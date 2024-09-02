#include "../includes/AudioManager.h"
#include "../includes/AssetPaths.h" // Include the header with asset paths
#include <iostream>

// Constructor to initialize the AudioManager and load the bounce sound.
AudioManager::AudioManager() {
    // Load the bounce sound from the asset path defined in AssetPaths.
    if (!bounceBuffer.loadFromFile(AssetPaths::bounceSound)) {
        std::cerr << "Failed to load bounce sound!" << std::endl; // Error handling if the sound fails to load.
    }
    bounceSound.setBuffer(bounceBuffer); // Set the buffer for the bounce sound.
}

// Method to play the bounce sound effect.
void AudioManager::playBounceSound() {
    bounceSound.play(); // Play the bounce sound.
}

// Method to play background music from the specified file.
// The loop parameter determines if the music should loop continuously.
void AudioManager::playMusic(const std::string& musicFile, bool loop) {
    if (backgroundMusic.openFromFile(musicFile)) { // Try to open the music file.
        backgroundMusic.setLoop(loop); // Set whether the music should loop.
        backgroundMusic.play(); // Start playing the music.
    }
    else {
        std::cerr << "Failed to load background music!" << std::endl; // Error handling if the music fails to load.
    }
}

// Method to stop the currently playing background music.
void AudioManager::stopMusic() {
    backgroundMusic.stop(); // Stop the background music.
}
