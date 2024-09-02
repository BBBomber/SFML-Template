#include "../includes/Ball.h"
#include "../includes/Paddle.h" // Include the Paddle header here

// Constructor that initializes the ball at the given x and y position, and sets the initial velocity.
Ball::Ball(float x, float y) {
    ball.setRadius(10);          // Set the radius of the ball (10 units).
    ball.setPosition(x, y);      // Position the ball at the given coordinates.
    ballVelocity = { -1.0f, -1.0f }; // Initialize the ball's velocity vector.
}

// Updates the ball's position based on the elapsed time and checks for boundary collisions.
void Ball::update(float deltaTime) {
    ball.move(ballVelocity * speed * deltaTime); // Move the ball based on its velocity and speed. (multiplied by delta time)

    // If the ball hits the top or bottom of the window, reverse its vertical direction.
    if (ball.getPosition().y < 0 || ball.getPosition().y > 590) {
        ballVelocity.y = -ballVelocity.y;
    }

    // Check if the ball goes out of bounds (left or right)
    if (ball.getPosition().x < 0 || ball.getPosition().x > 800) {
        reset();  // Reset the ball to the center
    }
    
    //we won't be using the checkCollision() method here but rather in the main game loop because we need to check it for both paddles
}

// Renders the ball onto the provided window.
void Ball::render(sf::RenderWindow& window) {
    window.draw(ball); // Draw the ball onto the window.
}

// Checks if the ball collides with the paddle and reverses the ball's horizontal direction if it does.
void Ball::checkCollision(Paddle& paddle) {
    if (ball.getGlobalBounds().intersects(paddle.getBounds())) {
        ballVelocity.x = -ballVelocity.x; // Reverse the horizontal velocity of the ball.
    }
}

// Returns the bounding rectangle of the ball for collision detection.
sf::FloatRect Ball::getBounds() {
    return ball.getGlobalBounds(); // Return the global bounds of the ball's shape.
}

// Resets the ball to its initial position in the center of the screen and sets its velocity.
void Ball::reset() {
    ball.setPosition(400, 300);    // Set the ball's position to the center of the screen.
    ballVelocity = { -1.0f, -1.0f }; // Reset the ball's velocity.
}
