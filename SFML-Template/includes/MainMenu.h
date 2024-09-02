#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "../includes/Button.h"
#include "../includes/GameState.h"

class MainMenu {
public:
    MainMenu(const sf::Font& font, GameState& gameState);
    void render(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);

private:
    std::vector<Button> buttons;
    GameState& gameState;  // Reference to game state to modify it
};

