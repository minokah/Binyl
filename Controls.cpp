/**
 * @brief Holds and provides functions to manipulate inner playback state. This file implements the Controls class which provides basic controls functionality for pausing and playing songs.
 * @author Armin Farhang
 * @author Brandon Luu
 */

#include "Controls.h"

// Constructor.
Controls::Controls() {}

// Destructor.
Controls::~Controls() {}

// Return the singleton instance.
Controls& Controls::getInstance() {
    static Controls instance;
    return instance;
}

// Check if paused or not
bool Controls::isPause() {
    return paused;
}

// Return if in queue mode or not.
bool Controls::isQueueMode() {
    return queue_mode;
}

// Set to paused or not.
void Controls::setPause(bool pause) {
    paused = pause;
}

// Set the queue mode.
void Controls::setQueueMode(bool mode) {
    queue_mode = mode;
}

// Adjust the volume by amount
void Controls::adjustVolume(int amount) {
    volume += amount;
    if (volume > 100) volume = 100;
    if (volume < 0) volume = 0;
}

// Return the volume
int Controls::getVolume() {
    return volume;
}

// Get the remaining time of a song.
int Controls::getTimeLeft() {
    return timeLeft;
}

// Set the remaining time of a song.
void Controls::setTimeLeft(int time) {
    timeLeft = time;
}
