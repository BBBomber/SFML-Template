#pragma once

#include <SFML/Graphics.hpp>

// Forward declaration of the Paddle class
// This allows the Ball class to reference the Paddle class without needing to include Paddle's header file.
class Paddle;

class Ball {
public:
    // Constructor that initializes the ball at the given x and y position.
    Ball(float x, float y);

    // Updates the ball's data every second
    void update(float deltaTime);

    // Renders the ball onto the provided window.
    void render(sf::RenderWindow& window);

    // Checks for collisions between the ball and the paddle.
    void checkCollision(Paddle& paddle);

    // Returns the bounding rectangle of the ball for collision detection. A square around the ball
    sf::FloatRect getBounds();

    // Resets the ball to its initial position in the center.
    void reset();

private:
    sf::CircleShape ball;          // The SFML circle shape representing the ball.
    sf::Vector2f ballVelocity;     // The velocity of the ball in 2D space.
    float speed = 300.0f;          // Speed of the ball.
};
