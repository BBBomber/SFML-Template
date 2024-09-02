#pragma once

#include <SFML/Graphics.hpp>

class Ball;

class Paddle {
public:
    // Constructor that initializes the paddle at the given x and y position, and sets the keys for movement.
    Paddle(float x, float y, sf::Keyboard::Key upKey, sf::Keyboard::Key downKey);

    void update(float deltaTime);
    void render(sf::RenderWindow& window, sf::Shader* shader = nullptr); // Add shader parameter with default null
    sf::FloatRect getBounds();
    void move(float dx, float dy);
    void setPosition(sf::Vector2f newPos);

    void updateAI(float deltaTime, Ball& ball, float windowWidth); // Method for AI control

    sf::RectangleShape& getShape();

private:

    sf::RectangleShape paddle;    // The SFML rectangle shape representing the paddle.
    float paddleSpeed = 400.0f;   // Speed of the paddle.
    sf::Keyboard::Key upKey, downKey; // Keys for moving the paddle up and down.

    // New variables to replace magic numbers
    const sf::Vector2f size = { 10.0f, 70.0f };  // Size of the paddle
    const float windowHeight = 600.0f;          // Window height for boundary checking
    const float aiSpeed = 450.0f;

    //ai movement variables
    float targetY = 0.0f;   // The y-position the AI paddle is moving towards
    float updateInterval = 0.1f;  // Time interval between updates (in seconds)
    float timeSinceLastUpdate = 0.0f;  // Time since the last position update
    float stopTolerance = 5.0f;  // Tolerance value for stopping near the target position
};
