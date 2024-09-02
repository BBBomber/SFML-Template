#pragma once

#include <SFML/Graphics.hpp>

// Forward declaration of the Paddle class
// This allows the Ball class to reference the Paddle class without needing to include Paddle's header file.
class Paddle;
class AudioManager;

class Ball {
public:
    // Constructor that initializes the ball at the given x and y position.
    Ball(float x, float y);

    // Updates the ball's data every second
    void update(float deltaTime);

    // Renders the ball onto the provided window.
    void render(sf::RenderWindow& window);

    // Checks for collisions between the ball and the paddle.
    void checkCollision(Paddle& paddle, AudioManager& audioManager);

    // Returns the bounding rectangle of the ball for collision detection. A square around the ball
    sf::FloatRect getBounds();

    // Resets the ball to its initial position in the center.
    void reset();

    sf::Vector2f getVelocity();

private:
    sf::CircleShape ball;          // The SFML circle shape representing the ball.
    sf::Vector2f ballVelocity;     // The velocity of the ball in 2D space.
    float speed = 450.0f;          // Speed of the ball.

    // New variables to replace magic numbers
    const float radius = 10.0f;            // Radius of the ball
    const sf::Vector2f initialPosition = { 400.0f, 300.0f };  // Initial/reset position of the ball
    const sf::Vector2f initialVelocity = { -1.0f, -1.0f };    // Initial velocity of the ball
    const float windowWidth = 800.0f;      // Width of the game window
    const float windowHeight = 600.0f;     // Height of the game window
};
