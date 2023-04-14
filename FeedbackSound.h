#ifndef FEEDBACK_SOUND_H
#define FEEDBACK_SOUND_H

#include <iostream>
#include <SFML/Audio.hpp>

/**
    @brief Play feedback sounds upon an action. This header provides the FeedbackSound class for playing a sound upon some action. 
    @author Irfan Rahul Sharif
    @author Brandon Luu
*/
class FeedbackSound {
    private:
        /**
         * @brief Sound buffer.
         */
        sf::SoundBuffer buffer;

        /**
            @brief Play the sound.
            @brief The sound buffer to be played.
        */
        void playSound(sf::SoundBuffer* buffer);

        /**
         * @brief Constructor for an instsance of FeedbackSound.
         */
        FeedbackSound();

        /**
         * @brief Destructor for an instance of FeedbackSound.
         */
        ~FeedbackSound();

    public:
        /**
        * @brief Method to initialize and return a single FeedbackSound instance.
        * @return Returns the FeedbackSound instance.
        */
        static FeedbackSound& getInstance();

        /**
         * @brief Play the "added to queue" sound.
         */
        void queueadd_sound();

        /**
         * @brief Play the "play" or "pause" sound.
         */
        void playpause_sound();

        /**
         * @brief Play the "skip next" sound.
         */
        void skipnext_sound();

        /**
         * @brief Play the "queue mode toggle" sound.
         */
        void queuemode_sound();

        /**
         * @brief Play the "volume adjust" sound.
         */
        void volume_sound();

        /**
         * @brief Play the "shuffle" sound.
         */
        void shuffle_sound();

        /**
         * @brief Play the "invlaid" sound.
         */
        void invalid_sound();

        /**
         * @brief Play the "clear queue" sound.
         */
        void clear_sound();

        /**
        * @brief Delete the copy constructor.
        */
        FeedbackSound(const FeedbackSound&) = delete;

        /**
        * @brief Delete the assignment operator.
        */
        FeedbackSound& operator=(const FeedbackSound&) = delete;
};
#endif