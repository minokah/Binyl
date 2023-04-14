/**
 * @brief Provides functions to interface with the Spotify API. This file implements the SpotifyService class for sending requests to the Spotify API.
 * @author Brandon Luu
*/

#include <iostream>
using namespace std;

#include "SpotifyService.h"

// Constructor.
SpotifyService::SpotifyService() {}

// Destructor.
SpotifyService::~SpotifyService() {}

// Return the singleton instance.
SpotifyService& SpotifyService::getInstance() {
    static SpotifyService instance;
    return instance;
}

// Initialize the underlying Spotify CURL class
void SpotifyService::init(string code, int access) {
    // New token
    if (access == 0) {
        SpotifyWebRequest spotify(code, access);
        this->code = spotify.getAccessToken();
        this->access = 1;
    }
    // Token already grabbed, don't grab another one
    else {
        this->code = code;
        this->access = access;
    }
}

// Get info about playing song
string SpotifyService::getPlaying() {
    SpotifyWebRequest spotify(code, access);
    spotify.execute("https://api.spotify.com/v1/me/player/currently-playing", spotify.req_GET);
    return spotify.result();
}

// Get JSON about a song
string SpotifyService::getSong(string id) {
    SpotifyWebRequest spotify(code, access);
    spotify.execute("https://api.spotify.com/v1/tracks/" + id, spotify.req_GET);
    return spotify.result();
}

// Get JSON about a playlist
string SpotifyService::getPlaylist(string id, int offset = 0) {
    SpotifyWebRequest spotify(code, access);
    spotify.execute("https://api.spotify.com/v1/playlists/" + id + "?offset=" + to_string(offset), spotify.req_GET);
    return spotify.result();
}

// Get JSON about an album
string SpotifyService::getAlbum(string id, int offset = 0) {
    SpotifyWebRequest spotify(code, access);
    spotify.execute("https://api.spotify.com/v1/albums/" + id + "?offset=" + to_string(offset), spotify.req_GET);
    return spotify.result();
}

// Set the volume
void SpotifyService::setVolume(int volume) {
    SpotifyWebRequest spotify(code, access);
    spotify.execute("https://api.spotify.com/v1/me/player/volume?volume_percent=" + to_string(volume), spotify.req_PUT);
}

// Start playing music
void SpotifyService::play() {
    SpotifyWebRequest spotify(code, access);
    spotify.execute("https://api.spotify.com/v1/me/player/play", spotify.req_PUT);
}

// Pause the music
void SpotifyService::pause() {
    SpotifyWebRequest spotify(code, access);
    spotify.execute("https://api.spotify.com/v1/me/player/pause", spotify.req_PUT);
}

// Skip to the next song
void SpotifyService::skipNext() {
    SpotifyWebRequest spotify(code, access);
    spotify.execute("https://api.spotify.com/v1/me/player/next", spotify.req_POST);
}

// Skip to the previous song
void SpotifyService::skipPrevious() {
    SpotifyWebRequest spotify(code, access);
    spotify.execute("https://api.spotify.com/v1/me/player/previous", spotify.req_POST);
}

// Add a song to the queue
void SpotifyService::queue(string url) {
    SpotifyWebRequest spotify(code, access);
    spotify.execute("https://api.spotify.com/v1/me/player/queue?uri=spotify:track:" + url, spotify.req_POST);
}