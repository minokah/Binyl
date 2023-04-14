#ifndef SONG_H
#define SONG_H

#include <string>
#include "User.h"

/**
 * @brief Holds song information (like name, artists, etc.). This header provides the Song class for holding song data.
 * @author Brandon Luu
*/
class Song {
    private:
        /**
         * @brief The user who requested the song.
        */
        User user;

        /**
         * @brief The unique ID of the song. 
        */
        std::string id;

        /**
         * @brief The name of the song.
        */
        std::string name;

        /**
         * @brief The song's associated album name.
        */
        std::string album;

        /**
         * @brief The song's artist's name.
        */
        std::string artist;

        /**
         * @brief A link to the cover art of the song. 
        */
        std::string coverArt;

        /**
         * @brief The song's total duration in seconds. 
        */
        int duration;

    public:
        /**
         * @brief A default constructor for the Song class. 
        */
        Song();

        /**
         * @brief A full constructor for the Song class.
         * @param user The user who requested the song.
         * @param id The id of the song. 
         * @param name The name of the song. 
         * @param duration The duration of the song in seconds. 
         * @param album The song's album's name. 
         * @param artist The song's artist's name. 
         * @param coverArt A link to the cover art of the song. 
        */
        Song(User user, std::string id, std::string name, int duration, std::string album, std::string artist, std::string coverArt); 
        
        /**
         * @brief Method to get the ID of the song. 
         * @return The ID of the song.
        */
        std::string getID();

        /**
         * @brief Method to get the user who requested the song. 
         * @return The user who requested the song.
        */
        User getUser();

        /**
         * @brief Method to get the artist who made the song. 
         * @return The song's artist.
        */
        std::string getArtist();

        /**
         * @brief Method to get the name of the song. 
         * @return The name of the song.
        */
        std::string getName();
        
        /**
         * @brief Method to get the song's album. 
         * @return The song's album's name.
        */
        std::string getAlbum();
       
        /**
         * @brief Method to get the cover art of the song. 
         * @return The cover art of the song.
        */
        std::string getCoverArt();
        
        /**
         * @brief Method to get the duration of the song. 
         * @return The duration of the song.
        */
        int getDuration();
};

#endif
