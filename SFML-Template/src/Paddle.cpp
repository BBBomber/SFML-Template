#include "../includes/Paddle.h"
#include "../includes/Ball.h"
#include <cstdlib>  // For std::rand()

Paddle::Paddle(float x, float y, sf::Keyboard::Key upKey, sf::Keyboard::Key downKey)
    : upKey(upKey), downKey(downKey) {
    paddle.setSize(size);                // Use the size variable
    paddle.setPosition(x, y);            // Set the initial position
}

void Paddle::update(float deltaTime) {
    if (sf::Keyboard::isKeyPressed(upKey) && paddle.getPosition().y > 0) {
        paddle.move(0, -paddleSpeed * deltaTime);
    }
    else if (sf::Keyboard::isKeyPressed(downKey) && paddle.getPosition().y < windowHeight - size.y) {  // Window height minus paddle height
        paddle.move(0, paddleSpeed * deltaTime);
    }
}

void Paddle::render(sf::RenderWindow& window) {
    window.draw(paddle);
}

sf::FloatRect Paddle::getBounds() {
    return paddle.getGlobalBounds();
}

void Paddle::move(float dx, float dy) {
    paddle.move(dx, dy);
}

void Paddle::setPosition(sf::Vector2f newPos)
{
    paddle.setPosition(newPos);
}

void Paddle::updateAI(float deltaTime, Ball& ball, float windowWidth) {
    timeSinceLastUpdate += deltaTime;

    if (timeSinceLastUpdate >= updateInterval) {
        // Predict where the ball will be when it reaches the AI paddle's x position
        float ballY = ball.getBounds().top + ball.getBounds().height / 2.0f;
        float ballSpeedX = ball.getVelocity().x;
        float ballSpeedY = ball.getVelocity().y;

        // Calculate the time it will take for the ball to reach the AI paddle's x position
        float timeToReachPaddle = (windowWidth - paddle.getPosition().x) / ballSpeedX;

        // Predict the y position where the ball will be when it reaches the paddle
        float predictedY = ballY + ballSpeedY * timeToReachPaddle;

        // Add some randomness to make the AI less predictable
        float randomOffset = (std::rand() % 30) - 15; // Random offset between 10 and - 10
        targetY = predictedY + randomOffset;

        timeSinceLastUpdate = 0.0f;
    }

    // Get the current y position of the paddle
    float paddleY = paddle.getPosition().y + paddle.getSize().y / 2.0f;

    // Determine the direction to move (towards the target)
    float direction = 0.0f;

    // Move the paddle only if it is outside the stop tolerance
    if (std::abs(targetY - paddleY) > stopTolerance) {
        direction = (targetY > paddleY) ? 1.0f : -1.0f;
    }

    paddle.move(0.0f, direction * aiSpeed * deltaTime);


    // Keep the paddle within the window bounds
    if (paddle.getPosition().y < 0) {
        paddle.setPosition(paddle.getPosition().x, 0);
    }
    else if (paddle.getPosition().y + paddle.getSize().y > windowHeight) {
        paddle.setPosition(paddle.getPosition().x, windowHeight - paddle.getSize().y);
    }

}