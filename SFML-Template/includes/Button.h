#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

class Button {
public:
    Button(const sf::Font& font, const std::string& text, float x, float y, float width = 200.0f, float height = 50.0f,
        const sf::Color& buttonColor = sf::Color::Blue, const sf::Color& textColor = sf::Color::White,
        const sf::Color& borderColor = sf::Color::Black, float borderThickness = 2.0f,
        std::function<void()> onClick = []() {});

    void render(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);

private:
    sf::Text buttonText;
    sf::RectangleShape buttonShape;
    std::function<void()> onClick;

    void init(const sf::Font& font, const std::string& text, float x, float y, float width, float height,
        const sf::Color& buttonColor, const sf::Color& textColor, const sf::Color& borderColor,
        float borderThickness);
};