#pragma once

#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Paddle.h"
#include "AudioManager.h"
#include "GameState.h"

class Game {
public:
    Game();              // Constructor to initialize the game
    void run();          // Runs the main game loop

private:
    void processEvents(); // Handles input and window events
    void update(float deltaTime); // Updates game objects based on elapsed time
    void render();        // Renders the game objects on the window
    void drawMiddleLine(); // Draws the middle line on the screen

    // Window properties
    sf::Vector2u windowSize = { 800, 600 };  // Window size (width, height)
    std::string windowTitle = "Pong - PvP Mode";  // Window title

    // Paddle positions
    sf::Vector2f player1Position = { 10.0f, 250.0f };
    sf::Vector2f player2Position = { 780.0f, 250.0f };

    // Ball position
    sf::Vector2f ballPosition = { 400.0f, 300.0f };

    sf::RenderWindow window;
    Paddle player1;
    Paddle player2;
    Ball ball;
    AudioManager audioManager;
    sf::Clock clock;
    GameState gameState;

    sf::RectangleShape middleLine; // Variable for the middle line
};

