/**
 * @brief Holds song information (like name, artists, etc.). This file implements the Song class for holding song data.
 * @author Brandon Luu
*/

#include "Song.h"
#include "User.h"
#include <string>

using namespace std;

Song::Song() {
    this->id = -1;
    this->artist = "Artist Name";
    this->name = "Song Name";
    this->album = "Album Name";
    this->coverArt = "";
    this->duration = 0;
}

Song::Song(User user, string id, string name, int duration, string album, string artist, string coverArt) {
    this->id = id;
    this->user = user;
    this->artist = artist;
    this->name = name;
    this->album = album;
    this->coverArt = coverArt;
    this->duration = duration;
}

string Song::getID() {
    return id;
}

User Song::getUser() {
    return user;
}

string Song::getArtist() {
    return artist;
}

string Song::getName() {
    return name;
}

string Song::getAlbum() {
    return album;
}

string Song::getCoverArt() {
    return coverArt;
}

int Song::getDuration() {
    return duration;
}
