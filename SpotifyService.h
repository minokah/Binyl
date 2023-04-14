#ifndef SPOTIFYSERVICE_H
#define SPOTIFYSERVICE_H

#include <iostream>
#include "SpotifyWebRequest.h"

/**
 * @brief Provides functions to interface with the Spotify API. This header provides the SpotifyService class for sending requests to the Spotify API.
 * @author Brandon Luu
*/
class SpotifyService {
    private:
        /**
          @brief The Spotify access code.
        */
        std::string code;

        /**
          @brief Whether the access code has already been authenciated or not.
        */
        int access;

        /**
            @brief Default Constructor for an instance of SpotifyService.
        */
        SpotifyService();
        
        /**
            @brief Constructor for an instance of SpotifyService.
        */
        SpotifyService(std::string code, int access = 0);

        /**
        * @brief Destructor for an instance of SpotifyService.
        */
        ~SpotifyService();

    public:
        /**
        * @brief Method to initialize and return a single SpotifyService instance.
        * @return Returns the SpotifyService instance.
        */
        static SpotifyService& getInstance();

        /**
            @brief Initializes the Spotify API service.
            @param code The Spotify authorization token.
            @param access Whether the auth token is already authorized (your code is actually an access token) or not.
        */
        void init(std::string code, int access);

        /**
            @brief Gets infomration about the currently playing song.
            @return Returns the JSON information about the currently playing song.
        */
        std::string getPlaying();

        /**
            @brief Gets infomration about a song.
            @param id The Spotify ID of the song (ex. The text after "track:" in spotify:track:57fqmDaokbxZ3TaB0jp39q).
            @return Returns the JSON information about a song.
        */
        std::string getSong(std::string id);

        /**
            @brief Gets infomration about a playlist.
            @param id The Spotify ID of the playlist (ex. The text after "playlist:" in spotify:playlist:28Iy9h5Xzax5dVbwmrgPxa).
            @return Returns the JSON information about a playlist.
        */
        std::string getPlaylist(std::string id, int offset);

        /**
            @brief Gets infomration about an album.
            @param id The Spotify ID of the album (ex. The text after "album:" in spotify:album:2ivNJLSx8Rbvnsvcn01Yt3).
            @return Returns the JSON information about an album.
        */
        std::string getAlbum(std::string id, int offset);

        /**
            @brief Sets the volume of the active device.
            @param volume The volume (from 0 to 100).
        */
        void setVolume(int volume);

        /**
            @brief Begin playback of the active device.
        */
        void play();

        /**
            @brief Pause playback of the active device.
        */
        void pause();

        /**
            @brief Skip to the next song in the Spotify queue.
        */
        void skipNext();

        /**
            @brief Skip to the previous song in the Spotify queue.
        */
        void skipPrevious();

        /**
            @brief Add a song to the Spotify queue.
            @param url The Spotify song's URL (ex. 57fqmDaokbxZ3TaB0jp39q).
        */
        void queue(std::string url);
};

#endif
