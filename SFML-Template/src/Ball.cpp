#include "../includes/Ball.h"
#include "../includes/Paddle.h"
#include "../includes/AudioManager.h"

Ball::Ball(float x, float y) {
    ball.setRadius(radius);                  // Use the radius variable
    ball.setPosition(x, y);                  // Initial position passed through constructor
    ballVelocity = initialVelocity;          // Initialize the ball's velocity vector with initial velocity
}

void Ball::update(float deltaTime) {
    ball.move(ballVelocity * speed * deltaTime);

    // Check if the ball hits the top or bottom of the window
    if (ball.getPosition().y < 0 || ball.getPosition().y > windowHeight - 2 * radius) {  // Window height minus ball diameter
        ballVelocity.y = -ballVelocity.y;
    }

}

void Ball::render(sf::RenderWindow& window, sf::Shader* shader) {
    if (shader) {
        window.draw(ball, shader); // Draw with shader
    }
    else {
        window.draw(ball); // Draw without shader
    }
}

void Ball::checkCollision(Paddle& paddle, AudioManager& audioManager) {
    if (ball.getGlobalBounds().intersects(paddle.getBounds())) {
        ballVelocity.x = -ballVelocity.x;  // Reverse the horizontal velocity of the ball
        audioManager.playBounceSound();
    }
}

sf::FloatRect Ball::getBounds() {
    return ball.getGlobalBounds();
}

void Ball::reset() {
    ball.setPosition(initialPosition);     // Reset to the initial position
    ballVelocity = initialVelocity;        // Reset the ball's velocity to the initial value
}

sf::Vector2f Ball::getVelocity()
{
    return ballVelocity;
}

sf::CircleShape& Ball::getShape()
{
    return ball;
}


