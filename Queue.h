#ifndef QUEUE_H
#define QUEUE_H

#include <string>
#include <vector>
#include "./Song.h"

/**
 * @brief Queue class for holding songs. This header provides the Queue class for storing songs in a queue.
 * @author Endreas Yohannes
 * @author Brandon Luu
 */
class Queue {
    private:
        /**
        * @brief The storage for the songs.
        */
        std::vector<Song> queue;

        /**
        * @brief Constructor for an instance of SpotifyService.
        */
        Queue(); 

        /**
        * @brief Destructor for an instance of SpotifyService.
        */
        ~Queue();

    public:
        /**
        * @brief Method to initialize and return a single Queue instance.
        * @return Returns the Queue instance.
        */
        static Queue& getInstance();

        /**
        * @brief Add a song to the back of the queue.
          @param song The song to add.
        */
        void enqueueBack(Song song);

        /**
        * @brief Add a song to the front of the queue.
          @param song The song to add.
          @param pos The index position.
        */
        void enqueueFront(Song song, int pos);

        /**
        * @brief Remove a song to the queue.
          @return The song data that was dequeued.
        */
        Song dequeue();

        /**
        * @brief Clears the queue.
        */
        void clear();

        /**
        * @brief Shuffles the queue.
        */
        void shuffle();

        /**
        * @brief See the size of the queue.
          @return Returns the size of the queue.
        */
        int size();

        /**
        * @brief Get a list of the next n songs.
          @param amount The n songs you want.
          @return Returns a list of the next n songs.
        */
        std::vector<Song> peekNext(int amount);
};

#endif
