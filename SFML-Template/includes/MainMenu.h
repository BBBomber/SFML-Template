#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "../includes/Button.h"
#include "../includes/GameState.h"
#include "../includes/AssetPaths.h"

class MainMenu {
public:
    MainMenu(const sf::Font& font, GameState& gameState);
    void render(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);

private:
    std::vector<Button> buttons;
    GameState& gameState;  // Reference to game state to modify it

    void initializeBackground();
    void initializeTitle(const sf::Font& font);
    void initializeButtons(const sf::Font& font);

    sf::Texture backgroundTexture; // Texture for the background image
    sf::Sprite backgroundSprite;   // Sprite to display the background image
    sf::Text titleText;            // Text for the title
};

