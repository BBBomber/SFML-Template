#include "../includes/Paddle.h"

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
