#ifndef CONTROLS_H
#define CONTROLS_H

/**
 * @brief Holds and provides functions to manipulate inner playback state. This header provides the Controls class which provides basic controls functionality for pausing and playing songs.
 * @author Armin Farhang
 * @author Brandon Luu
 */
class Controls {
private:
    /**
     * @brief Indicator of play status.
     * True for paused, false for playing.
    */
    bool paused = false;
    
    /**
     * @brief Indicator of queue mode.
       If queue mode is on, then add to the BACK of the queue, otherwise put it to the front.
     * True means we're in queue mode, false means the opposite.
    */
    bool queue_mode = true;

    /**
     * @brief The current volume of the Spotify player.
    */
    int volume = 100;

    /**
     * @brief Time remaining on the current song in seconds.
    */
    int timeLeft = 0;

    /**
     * @brief Constructor for an instance of Controls.
    */
    Controls();

    /**
     * @brief Destructor for an instance of Controls.
    */
    ~Controls();

public:
    /**
     * @brief Method to initialize and return a single Controls instance.
     * @return Returns the Controls instance.
    */
    static Controls& getInstance();

    /**
     * @brief Method to return the current pause status.
     * @return True if the song is paused, false otherwise.
    */
    bool isPause();

    /**
     * @brief Method to return the current queue mode.
     * @return The state of the queue mode.
    */
    bool isQueueMode();

    /**
     * @brief Method to set the pause status of Controls.
     * @param pause The desired pause status (true for pause, false for play).
    */
    void setPause(bool pause);

    /**
     * @brief Method to turn queue mode on and off in Controls.
     * @param mode The desired queue mode (true for queue mode, false for non-queue mode).
    */
    void setQueueMode(bool mode);

    /**
     * @brief Increase (or decrease) the Spotify player's volume by the specified amount.
     * @param amount The amount to increase by.
    */
    void adjustVolume(int amount);

    /**
     * @brief Return the volume.
     * @return The volume.
    */
    int getVolume();

    /**
     * @brief Method to get the time left in the current song.
     * @return The time left of the current song in seconds.
    */
    int getTimeLeft();

    /**
     * @brief Method to set the time of the current song.
     * @param time The desired time stamp in seconds. 
    */
    void setTimeLeft(int time);

    /**
     * @brief Delete the copy constructor.
    */
    Controls(const Controls&) = delete;

    /**
     * @brief Delete the assignment operator.
    */
    Controls& operator=(const Controls&) = delete;
};

#endif // CONTROLS_H
