#include "../includes/Paddle.h"

// Constructor that initializes the paddle at the given x and y position and sets the keys for movement.
Paddle::Paddle(float x, float y, sf::Keyboard::Key upKey, sf::Keyboard::Key downKey)
    : upKey(upKey), downKey(downKey) {
    paddle.setSize({ 10, 100 });   // Set the size of the paddle (10 units wide, 100 units tall).
    paddle.setPosition(x, y);      // Position the paddle at the given coordinates.
}

// Updates the paddle's position based on user input and the elapsed time.
void Paddle::update(float deltaTime) {
    // Move the paddle up if the up key is pressed and the paddle is within the window bounds.
    if (sf::Keyboard::isKeyPressed(upKey) && paddle.getPosition().y > 0) {
        paddle.move(0, -paddleSpeed * deltaTime);
    }
    // Move the paddle down if the down key is pressed and the paddle is within the window bounds.
    else if (sf::Keyboard::isKeyPressed(downKey) && paddle.getPosition().y < 500) {
        paddle.move(0, paddleSpeed * deltaTime);
    }
}

// Renders the paddle onto the provided window.
void Paddle::render(sf::RenderWindow& window) {
    window.draw(paddle); // Draw the paddle onto the window.
}

// Returns the bounding rectangle of the paddle for collision detection.
sf::FloatRect Paddle::getBounds() {
    return paddle.getGlobalBounds(); // Return the global bounds of the paddle's shape.
}

// Moves the paddle by the given dx and dy values.
void Paddle::move(float dx, float dy) {
    paddle.move(dx, dy); // Move the paddle by the specified amounts.
}
