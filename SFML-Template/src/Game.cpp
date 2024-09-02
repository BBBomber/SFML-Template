#include "../includes/Game.h"
#include <iostream>

// Constructor initializes the game objects and sets the initial game state
Game::Game()
    : window(sf::VideoMode(windowSize.x, windowSize.y), windowTitle),
    player1(player1Position.x, player1Position.y, sf::Keyboard::W, sf::Keyboard::S),
    player2(player2Position.x, player2Position.y, sf::Keyboard::Up, sf::Keyboard::Down),
    ball(ballPosition.x, ballPosition.y),
    gameState(GameState::PlayingPvP) // Set default game state to PlayingPvP
{
    window.setFramerateLimit(60); // Set the frame rate limit
}

// The main game loop, which keeps the window open and updates the game state
void Game::run() {
    while (window.isOpen()) {
        processEvents();           // Handle input and window events
        update(clock.restart().asSeconds()); // Update game objects based on time
        render();                  // Render the game objects
    }
}

// Handles input and window events, like closing the window
void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close(); // Close the window if the close button is clicked
        }
    }
}

// Updates the positions and states of the paddles and ball
void Game::update(float deltaTime) {
    player1.update(deltaTime);
    player2.update(deltaTime);
    ball.update(deltaTime);

    // Check for collisions between the ball and the paddles
    ball.checkCollision(player1, audioManager);
    ball.checkCollision(player2, audioManager);
}

// Renders the paddles and the ball on the window
void Game::render() {
    window.clear();                // Clear the window
    player1.render(window);        // Draw player 1's paddle
    player2.render(window);        // Draw player 2's paddle
    ball.render(window);           // Draw the ball
    window.display();              // Display the contents of the window on the screen
}
