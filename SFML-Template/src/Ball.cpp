#include "../includes/Ball.h"
#include "../includes/Paddle.h"
#include "../includes/AudioManager.h"
#include <iostream>

Ball::Ball(float x, float y) {
    ball.setRadius(radius);                  // Use the radius variable
    ball.setPosition(x, y);                  // Initial position passed through constructor
    ballVelocity = initialVelocity;          // Initialize the ball's velocity vector with initial velocity
}

void Ball::update(float deltaTime, const sf::RenderWindow& window) {
    ball.move(ballVelocity * speed * deltaTime);
    checkWindowCollision(window);

}

void Ball::render(sf::RenderWindow& window) {
    window.draw(ball);
}

void Ball::checkCollision(Paddle& paddle, AudioManager& audioManager) {
    sf::FloatRect ballBounds = ball.getGlobalBounds();
    sf::FloatRect paddleBounds = paddle.getBounds();

    // Check if the ball collides with the paddle
    if (ballBounds.intersects(paddleBounds)) {
        std::cout << "Collision detected!" << std::endl;  // Debug statement

        // Play bounce sound
        audioManager.playBounceSound();

        // Calculate the relative position where the ball hits the paddle
        float paddleCenterY = paddleBounds.top + paddleBounds.height / 2.0f;
        float collidePoint = (ball.getPosition().y - paddleCenterY) / (paddleBounds.height / 2.0f);

        // Restrict the collide point between -1 and 1
        collidePoint = std::max(-1.0f, std::min(1.0f, collidePoint));

        const float pi = 3.14159265358979323846f;
        float angleRad = (pi / 3.0f) * collidePoint;  // Restrict angle to 45 degrees

        // Reverse horizontal velocity
        ballVelocity.x = -ballVelocity.x;

        // Calculate new velocity based on the angle of collision
        float newSpeed = std::sqrt(ballVelocity.x * ballVelocity.x + ballVelocity.y * ballVelocity.y);
        ballVelocity.x = (ballVelocity.x > 0 ? 1 : -1) * newSpeed * std::cos(angleRad);
        ballVelocity.y = newSpeed * std::sin(angleRad);

        float minMoveDistance = 4.0f; // Minimum distance to move the ball away from the paddle

        if (ballVelocity.x > 0) {
            ball.setPosition(paddleBounds.left + paddleBounds.width + radius + minMoveDistance, ball.getPosition().y);
        }
        else {
            ball.setPosition(paddleBounds.left - radius - minMoveDistance, ball.getPosition().y);
        }

        // Log final ball position and velocity for debugging
        std::cout << "Ball new velocity: (" << ballVelocity.x << ", " << ballVelocity.y << ")" << std::endl;
        std::cout << "Ball new position: (" << ball.getPosition().x << ", " << ball.getPosition().y << ")" << std::endl;
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

void Ball::checkWindowCollision(const sf::RenderWindow& window)
{
    sf::FloatRect ballBounds = ball.getGlobalBounds();

    // Get the viewport size based on the current view
    sf::View view = window.getView();
    sf::Vector2f viewSize = view.getSize();
    sf::Vector2f viewCenter = view.getCenter();

    // Calculate the top and bottom boundaries of the viewport
    float viewTop = viewCenter.y - (viewSize.y / 2.0f);
    float viewBottom = viewCenter.y + (viewSize.y / 2.0f);

    // Check if the ball hits the top or bottom of the viewport
    if (ballBounds.top < viewTop)
    {
        // Hit the top: reverse vertical velocity and reposition
        ballVelocity.y = -ballVelocity.y;
        ball.setPosition(ball.getPosition().x, viewTop + radius +5.0f);
    }
    else if (ballBounds.top + ballBounds.height > viewBottom)
    {
        // Hit the bottom: reverse vertical velocity and reposition
        ballVelocity.y = -ballVelocity.y;

        ball.setPosition(ball.getPosition().x, viewBottom - radius -8.0f);
    }
}


