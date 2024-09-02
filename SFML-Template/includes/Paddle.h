#pragma once

#include <SFML/Graphics.hpp>

class Paddle {
public:
    // Constructor that initializes the paddle at the given x and y position, and sets the keys for movement.
    Paddle(float x, float y, sf::Keyboard::Key upKey, sf::Keyboard::Key downKey);

    // Updates the paddle's position based on the elapsed time and user input.
    void update(float deltaTime);

    // Renders the paddle onto the provided window.
    void render(sf::RenderWindow& window);

    // Returns the bounding rectangle of the paddle for collision detection.
    sf::FloatRect getBounds();

    // Moves the paddle by the given dx and dy values.
    void move(float dx, float dy);

private:
    sf::RectangleShape paddle;    // The SFML rectangle shape representing the paddle.
    float paddleSpeed = 400.0f;   // Speed of the paddle.
    sf::Keyboard::Key upKey, downKey; // Keys for moving the paddle up and down.
};
