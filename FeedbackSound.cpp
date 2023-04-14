/**
    @brief Play feedback sounds upon an action. This file implements the FeedbackSound class for playing a sound upon some action. 
    @author Irfan Rahul Sharif
    @author Brandon Luu
*/

#include "FeedbackSound.h"

// Constructor.
FeedbackSound::FeedbackSound(){};

// Destructor.
FeedbackSound::~FeedbackSound(){};

// Return the singleton instance.
FeedbackSound& FeedbackSound::getInstance() {
    static FeedbackSound instance;
    return instance;
}

// Play the sound.
void FeedbackSound::playSound(sf::SoundBuffer* buffer){
    sf::Sound sound(*buffer);
    sound.play();
    while (sound.getStatus() == sf::Sound::Playing) {
        // Wait for the sound to finish playing
    }
}

// Load the card tapped sound and play it.
void FeedbackSound::queueadd_sound(){
    buffer.loadFromFile("assets/sounds/queueadd.wav");
    playSound(&buffer);
}

// Load the play sound and play it.
void FeedbackSound::playpause_sound(){
    buffer.loadFromFile("assets/sounds/playpause.wav");
    playSound(&buffer);
}

// Load the next sound and play it.
void FeedbackSound::skipnext_sound(){
    buffer.loadFromFile("assets/sounds/skipnext.wav");
    playSound(&buffer);
}

// Load the queue sound and play it.
void FeedbackSound::queuemode_sound(){
    buffer.loadFromFile("assets/sounds/queuemode.wav");
    playSound(&buffer);
}

// Load the volume sound and play it.
void FeedbackSound::volume_sound(){
    buffer.loadFromFile("assets/sounds/volume.wav");
    playSound(&buffer);
}

// Load the volume sound and play it.
void FeedbackSound::shuffle_sound(){
    buffer.loadFromFile("assets/sounds/shuffle.wav");
    playSound(&buffer);
}

// Load the invalid sound and play it.
void FeedbackSound::invalid_sound(){
    buffer.loadFromFile("assets/sounds/invalid.wav");
    playSound(&buffer);
}

// Load the clear queue sound and play it.
void FeedbackSound::clear_sound() {
    buffer.loadFromFile("assets/sounds/clear.wav");
    playSound(&buffer);
}