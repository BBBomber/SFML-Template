#pragma once

#include <SFML/Audio.hpp>

// The AudioManager class manages all audio-related functionality,
// including playing sound effects and background music.
class AudioManager {
public:
    // Constructor to initialize and load the necessary sound assets.
    AudioManager();

    // Method to play the bounce sound effect.
    void playBounceSound();

    // Method to play background music from the specified file.
    // The music can loop by default.
    void playMusic(const std::string& musicFile, bool loop = true);

    // Method to stop the currently playing background music.
    void stopMusic();

private:
    sf::SoundBuffer bounceBuffer;  // Buffer to hold the bounce sound data.
    sf::Sound bounceSound;         // Sound object to play the bounce sound.
    sf::Music backgroundMusic;     // Music object to handle background music playback.
};
