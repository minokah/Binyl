/**
    @file Binyl.cpp
    @brief The main program. Interfaces with all the classes.
    @author Brandon Luu

    Binyl: Spotify RFID Music Player
    Tap a Binyl card to add songs, change playback, and more!

    Authors: Brandon Luu, Irfan Rahul Sharif, Armin Farhang-Pour, Ryan Cook, Endreas Yohannes

    Visit this site and login to get a new code.
    Copy the 'code' value within the URL and run the program using:
        ./program [code]
        ./program [access token] 1

    https://accounts.spotify.com/authorize?response_type=code&scope=user-read-playback-state user-modify-playback-state&client_id=8692d0967e7d4bd4bf898c2c98b9e64b&redirect_uri=https://www.blank.org/
*/
#include <iostream>
using namespace std;

#include <string>
#include <thread>
#include <unistd.h>

#include "SpotifyService.h"
#include "RFIDModule/RFIDModule.h"
#include "GUI.h"
#include "FeedbackSound.h"
#include "GraphicsDisplay.h"
#include "User.h"
#include "Song.h"
#include "Queue.h"

#include "json.hpp"
using json = nlohmann::json;

// Declare threads in main beforehand
void guiThreadFunction(GUI* gui);
void rfidThreadFunction(GUI *gui);
void processSongThreadFunction(GUI *gui);

/**
    @brief Entry point for the program.
    @param argc Argument count.
    @param argv Should contain the Spotify token obtained from the authorization URL as the first argument.
*/
int main(int argc, char* argv[]) {
  // Check user sudo, if not then exit
  if (geteuid() != 0) {
    cout << "Binyl must be run as root (sudo)." << endl;
    return -1;
  }

  // Check and parse arguments
  if (argc < 2) {
    cout << "\nBinyl: Spotify RFID Music Player\n\nSpotify code missing\nVisit this site and login to get a new code.\n"
    "Copy the 'code' value within the URL and run the program using:\n"
    "\t./program [code]\n"
    "\t./program [access token] 1\n" << endl;
    cout << "https://accounts.spotify.com/authorize?response_type=code&scope=user-read-playback-state user-modify-playback-state&client_id=8692d0967e7d4bd4bf898c2c98b9e64b&redirect_uri=https://www.google.com/\n" << endl;
    return -1;
  }
  
  string code = string(argv[1]);
  int access = 0;
  if (argc == 3) access = stoi(argv[2]);

  cout << "\nBinyl: Spotify RFID Music Player\n\nTap your card to add songs, change playback, and more!\n\nAuthors: Brandon Luu, Irfan Rahul Sharif, Armin Farhang-Pour, Ryan Cook, Endreas Yohannes\n" << endl;

  // Initialize Spotify API service
  SpotifyService& spotify = SpotifyService::getInstance();
  spotify.init(code, access);
  spotify.setVolume(50);

  // Create classes
  GUI gui(1920, 1080, "Binyl", "w");
  GraphicsDisplay graphics;

  // Create needed threads: GUI, RFID reader, Song processor
  thread guiThread(guiThreadFunction, &gui);
  thread rfidThread(rfidThreadFunction, &gui);
  thread processSongThread(processSongThreadFunction, &gui);

  // Fork our process and run the physical display
  graphics.display("Welcome to Binyl!");

  // Stall until interrupt received
  while (true);

  return 0;
}

/**
    @brief Begins reading from the RFID reader and sends commands to the Spotify API.
    @param gui The GUI object.
*/
void rfidThreadFunction(GUI *gui) {
  SpotifyService& spotify = SpotifyService::getInstance();
  RFIDModule& rfid = RFIDModule::getInstance();
  Controls& controls = Controls::getInstance();
  FeedbackSound& feedback = FeedbackSound::getInstance();
  Queue& queue = Queue::getInstance();

  cout << "Card reader started!\n" << endl;
  while (true) {
    // get card type and check to see if valid
    string type = rfid.get(8);

    if (type == "track") {
      // Combine IDs as they are stored on two blocks
      string id1 = rfid.get(9);
      string id2 = rfid.get(10);
      string id = id1 + id2;

      string cardOwner = rfid.get(12);
      // Get song info (for use later...)
      json songjson = json::parse(spotify.getSong(id));

      // Stop if there is an error while queuing
      if (!songjson["error"].is_null()) {
        string error = songjson["error"]["message"];
        cout << "Error while queuing song: " << error << endl;
        break;
      }

      // Printing json object directly adds quotes around strings, this avoids that
      string songID = songjson["id"];
      string songName = songjson["name"];
      int songDuration = songjson["duration_ms"];
      string albumName = songjson["album"]["name"];
      string artistName = songjson["artists"][0]["name"];
      string albumArt = songjson["album"]["images"][0]["url"];
      
      // Create user and song, then queue
      User newUser(cardOwner);
      Song newSong(newUser, songID, songName, songDuration, albumName, artistName, albumArt);

      // In queue mode, insert at back. Otherwise, insert at front and play immediately.
      if (controls.isQueueMode()) queue.enqueueBack(newSong);
      else {
        queue.enqueueFront(newSong, 0);
        controls.setTimeLeft(0);
      }

      gui->flashCard(newSong, "single");
      feedback.queueadd_sound();
      cout << "[" << cardOwner << ": Queue Song] " << artistName << " - " << songName << endl;
    }

    // There is a limit where it can only get 100 songs at once
    // but we can use the offset flag to get around it
    else if (type == "playlist") {
      // Combine IDs as they are stored on two blocks
      string id1 = rfid.get(9);
      string id2 = rfid.get(10);
      string id = id1 + id2;

      string cardOwner = rfid.get(12);

      // Loop until we reach the end of the playlist
      int offset = 0;
      int queueIndex = 0;
      while (true) {
        json playlistjson = json::parse(spotify.getPlaylist(id, offset));

        // Stop if there is an error while getting playlist
        if (!playlistjson["error"].is_null()) {
          string error = playlistjson["error"]["message"];
          cout << "Error while queuing playlist: " << error << endl;
          break;
        }

        // Display that the card has been tapped *before* we queue it as the thread
        // will stall getting all the cards before it can display it

        // Printing json object directly adds quotes around strings, this avoids that
        string displayName = playlistjson["owner"]["display_name"];
        string playlistName = playlistjson["name"];
        string playlistArt = playlistjson["images"][0]["url"];
        User nobody("");
        Song newPlaylist(nobody, "", "", 0, playlistName, displayName, playlistArt);
        gui->flashCard(newPlaylist, "playlist");

        feedback.queueadd_sound();

        // Get songs in playlist
        json items = playlistjson["tracks"]["items"];
        int count = 0;
        for (count; count != items.size(); count++) {
          string songID = items[count]["track"]["id"];

          json songjson = json::parse(spotify.getSong(songID));

          // Get data
          string songName = songjson["name"];
          int songDuration = songjson["duration_ms"];
          string albumName = songjson["album"]["name"];
          string artistName = songjson["artists"][0]["name"];
          string albumArt = songjson["album"]["images"][0]["url"];
          
          // Create user and song, then queue
          User newUser(cardOwner);
          Song newSong(newUser, songID, songName, songDuration, albumName, artistName, albumArt);

          // Queue mode is on, queue at back. Otherwise, queue at front.
          if (controls.isQueueMode()) queue.enqueueBack(newSong);
          else {
            queue.enqueueFront(newSong, queueIndex);
            queueIndex++;
          }
        }

        // If the "next" field is defined, then continue getting the next set of 100 songs
        if (!playlistjson["tracks"]["next"].is_null()) offset += 100;
        else {
          // Finished, if not in queue mode play immediately
          if (!controls.isQueueMode()) controls.setTimeLeft(0);
          cout << "[" << cardOwner << ": Queue Playlist] " << displayName << " - " << playlistName << " [" << playlistjson["tracks"]["total"] << " song(s)]" << endl;
          break;
        }
      }
    }

    // There is a limit where it can only get 50 songs at once
    // but we can use the offset flag to get around it
    else if (type == "album") {
      // Combine IDs as they are stored on two blocks
      string id1 = rfid.get(9);
      string id2 = rfid.get(10);
      string id = id1 + id2;

      string cardOwner = rfid.get(12);

      // Loop until we reach the end of the playlist
      int offset = 0;
      int queueIndex = 0;
      while (true) {
        json albumjson = json::parse(spotify.getAlbum(id, offset));

        // Stop if there is an error while getting playlist
        if (!albumjson["error"].is_null()) {
        string error = albumjson["error"]["message"];
        cout << "Error while queuing album: " << error << endl;
        break;
      }

        // Get songs in album
        json items = albumjson["tracks"]["items"];
        string albumName = albumjson["name"];
        string artistName = albumjson["artists"][0]["name"];
        string albumArt = albumjson["images"][0]["url"];

        int count = 0;
        for (count; count != items.size(); count++) {
          string songID = items[count]["id"];
          string songName = items[count]["name"];
          int songDuration = items[count]["duration_ms"];

          // Get user and song, then queue
          User newUser(cardOwner);
          Song newSong(newUser, songID, songName, songDuration, albumName, artistName, albumArt);

          // Queue mode is on, queue at back. Otherwise, queue at back.
          if (controls.isQueueMode()) queue.enqueueBack(newSong);
          else {
            queue.enqueueFront(newSong, queueIndex);
            queueIndex++;
          }
        }

        // If the "next" field is defined, then continue getting the next set of 50 songs
        if (!albumjson["tracks"]["next"].is_null()) offset += 50;
        else {
          string albumName = albumjson["name"];
          string artistName = albumjson["artists"][0]["name"];
          string albumArt = albumjson["images"][0]["url"];

          User nobody("");
          Song newPlaylist(nobody, "", "", 0, albumName, artistName, albumArt);
          gui->flashCard(newPlaylist, "album");

          // Finished, if not in queue mode play immediately
          if (!controls.isQueueMode()) controls.setTimeLeft(0);

          feedback.queueadd_sound();
          cout << "[" << cardOwner << ": Queue Album] " << artistName << " - " << albumName << " [" << albumjson["tracks"]["total"] << " song(s)]" << endl;
          break;
        }
      }
    }
    // Toggle between pause and play
    else if (type == "toggleplay") {
      // Set to play
      if (controls.isPause()) {
        controls.setPause(false);
        spotify.play();
        gui->setPlayScreen();
        cout << "[Play] The player is now playing" << endl;
      }
      else {
        spotify.pause();
        controls.setPause(true);
        gui->setPauseScreen();
        cout << "[Pause] The player is now paused" << endl;
      }

      feedback.playpause_sound();
    }
    // Skip to the next song
    else if (type == "skipnext") {
      // Set time left to 0 and set GUI
      controls.setTimeLeft(0);
      gui->flashNextLogo();
      feedback.skipnext_sound();
      cout << "[Skip Next] The current song has been skipped" << endl;
    }
    // Shuffle the queue
    else if (type == "shuffle") {
      queue.shuffle();
      vector<Song> four = queue.peekNext(4);
      gui->setNextFour(four, queue.size());
      feedback.skipnext_sound();
      cout << "[Shuffle] The queue has been shuffled" << endl;
    }
    else if (type == "volume") {
      int amount = stoi(rfid.get(9));
      controls.adjustVolume(amount);
      spotify.setVolume(controls.getVolume());
      feedback.volume_sound();
      cout << "[Volume] The volume has been adjusted to " << to_string(controls.getVolume()) << endl;
    }
    else if (type == "queuemode") {
      // Set queue mode to true
      if (!controls.isQueueMode()) {
        controls.setQueueMode(true);
        gui->setQueueScreen();
        cout << "[Queue Mode] Now enabled" << endl;
      }
      else {
        controls.setQueueMode(false);
        gui->removeQueueScreen();
        cout << "[Queue Mode] Now disabled" << endl;
      }

      feedback.queuemode_sound();
    }
    else if (type == "clearqueue") {
      queue.clear();
      vector<Song> four = queue.peekNext(4);
      gui->setNextFour(four, queue.size());
      feedback.clear_sound();
      cout << "[Clear Queue] The queue has been cleared" << endl;
    }
    else {
      cout << "Invalid card!" << endl;
      feedback.invalid_sound();
    }

    // Delay for next card
    printf("\nNext card reading in 3 seconds...\n");
    sleep(3);
  }
}

/**
    @brief Begins processing songs in the queue to be played.
    @param gui The GUI object.
*/
void processSongThreadFunction(GUI *gui) {
  SpotifyService& spotify = SpotifyService::getInstance();
  Controls& controls = Controls::getInstance();
  Queue& queue = Queue::getInstance();

  int prevQueueSize = 0;

  while (true) {
    // Song still playing, decrement time and continue
    if (controls.getTimeLeft() > 0) {
      if (!controls.isPause()) controls.setTimeLeft(controls.getTimeLeft() - 1000);

      // Update GUI if queue size changed
      if (prevQueueSize != queue.size()) {
        // Get next 4 songs
        vector<Song> four = queue.peekNext(4);
        gui->setNextFour(four, queue.size());
        prevQueueSize = queue.size();
      }
    }
    else if (queue.size() > 0) {
      // Dequeue a song and play it
      Song song = queue.dequeue();

      // Queue up the song and set time left
      spotify.queue(song.getID());
      // Delay for queuing and then play
      sleep(1);
      spotify.skipNext();
      sleep(1);
      spotify.play();
      controls.setTimeLeft(song.getDuration());

      // Update GUI
      gui->setCurrentSong(song);
    }
    else gui->setEmpty();

    // Wait one second and loop
    sleep(1);
  }
}

/**
    @brief Begins running the GUI.
    @param gui The GUI object.
*/
void guiThreadFunction(GUI *gui) {
  gui->runScreen();

  // If the GUI has exited, exit the program
  return;
}