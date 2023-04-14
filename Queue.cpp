/**
 * @brief Queue class for holding songs. This file implements the Queue class for storing songs in a queue.
 * @author Endreas Yohannes
 * @author Brandon Luu
 */

#include <algorithm>
#include <random>
#include <vector>
#include <iterator>
#include <time.h>
#include "./Queue.h"

// Constructor
Queue::Queue() {
    this->queue = std::vector<Song>();
}

// Destructor
Queue::~Queue() {}

// Return the singleton instance
Queue& Queue::getInstance() {
    static Queue instance;
    return instance;
}

// Enqueue a song to the back
void Queue::enqueueBack(Song song) { 
    this->queue.push_back(song);
}

void Queue::enqueueFront(Song song, int pos = 0) {
    queue.insert(queue.begin() + pos, song);
}

// Dequeue a song
Song Queue::dequeue() {
    Song song = this->queue.front();
    this->queue.erase(queue.begin());
    return song;
}

// Clear the entire queue
void Queue::clear() {
    this->queue.clear();
}

// Shuffle the queue
void Queue::shuffle() {
    // Some found method on the internet to shuffle it
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(queue.begin(), queue.end(), gen);

    /*
    This does not seem to work that well

    srand(time(NULL));
    for (int i = 0; i < this->queue.size()*5; i++) {
        int index1 = rand() % (this->queue.size() - 1);
        int index2 = rand() % (this->queue.size() - 1);
        std::iter_swap(this->queue.begin() + index1, this->queue.begin() + index2);
    }
    */
}

// Return the size of the queue
int Queue::size() {
    return this->queue.size();
}

// Get a vector of the next n songs
std::vector<Song> Queue::peekNext(int amount) {
    std::vector<Song> subQueue;
    for (int i = 0; i != amount; i++) {
        // Stop if we are over the queue limit
        if (i == queue.size()) break;
        subQueue.push_back(queue.at(i));
    }
    return subQueue;
}
