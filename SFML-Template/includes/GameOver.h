#pragma once

#include <SFML/Graphics.hpp>
#include "../includes/Button.h"
#include "../includes/GameState.h"

class GameOver {
public:
    GameOver(const sf::Font& font, GameState& gameState);
    void setWinner(int player);  // Set the winner (1 for player 1, 2 for player 2)
    void render(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);

private:
    void initializeText(const sf::Font& font);
    void onMainMenuButtonClicked();  // Member function to handle the main menu button click

    sf::Text gameOverText;
    sf::Text winnerText;
    Button mainMenuButton;
    GameState& gameState;
};