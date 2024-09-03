#include "../includes/Button.h"

Button::Button(const sf::Font& font, const std::string& text, float x, float y, float width, float height,
    const sf::Color& buttonColor, const sf::Color& textColor, const sf::Color& borderColor,
    float borderThickness, std::function<void()> onClick)
    : onClick(onClick) {
    init(font, text, x, y, width, height, buttonColor, textColor, borderColor, borderThickness);
}

void Button::init(const sf::Font& font, const std::string& text, float x, float y, float width, float height,
    const sf::Color& buttonColor, const sf::Color& textColor, const sf::Color& borderColor,
    float borderThickness) {
    buttonShape.setSize(sf::Vector2f(width, height));
    buttonShape.setFillColor(buttonColor);
    buttonShape.setPosition(x, y);
    buttonShape.setOutlineColor(borderColor);
    buttonShape.setOutlineThickness(borderThickness);

    buttonText.setFont(font);
    buttonText.setString(text);
    buttonText.setCharacterSize(static_cast<unsigned int>(height / 2));  // Set character size relative to button height
    buttonText.setFillColor(textColor);
    buttonText.setPosition(
        x + (width / 2.0f) - (buttonText.getLocalBounds().width / 2.0f),
        y + (height / 2.0f) - (buttonText.getLocalBounds().height / 2.0f) - buttonText.getCharacterSize() / 4.0f
    );
}

void Button::render(sf::RenderWindow& window) {
    window.draw(buttonShape);
    window.draw(buttonText);
}

void Button::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

        if (buttonShape.getGlobalBounds().contains(worldPos)) {
            onClick(); // Trigger the button's action
        }
    }
}