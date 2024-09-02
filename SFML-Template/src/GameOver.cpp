#include "../includes/GameOver.h"
#include <iostream>

GameOver::GameOver(const sf::Font& font, GameState& gameState)
    : gameState(gameState),
    mainMenuButton(font, "Main Menu", 300.0f, 400.0f, 200.0f, 50.0f, sf::Color::Blue, sf::Color::White, sf::Color::Black, 2.0f, std::bind(&GameOver::onMainMenuButtonClicked, this))
{
    initializeText(font);
    // No need to call initializeButton here since the button is already initialized in the initializer list
}

void GameOver::initializeText(const sf::Font& font) {
    // Initialize Game Over text
    gameOverText.setFont(font);
    gameOverText.setString("Game Over");
    gameOverText.setCharacterSize(72);
    gameOverText.setStyle(sf::Text::Bold);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setPosition(
        (800.0f - gameOverText.getLocalBounds().width) / 2.0f,
        100.0f
    );

    // Initialize Winner text (to be set dynamically)
    winnerText.setFont(font);
    winnerText.setCharacterSize(48);
    winnerText.setFillColor(sf::Color::White);
    winnerText.setPosition(
        (800.0f - winnerText.getLocalBounds().width) / 2.0f,
        200.0f
    );
}

void GameOver::onMainMenuButtonClicked() {
    gameState = GameState::MainMenu;
    std::cout << "button clicked" << std::endl;
}

void GameOver::setWinner(int player) {
    if (player == 1) {
        winnerText.setString("Player 1 Wins!");
    }
    else {
        winnerText.setString("Player 2 Wins!");
    }
    // Center the winner text
    winnerText.setPosition(
        (800.0f - winnerText.getLocalBounds().width) / 2.0f,
        200.0f
    );
}

void GameOver::render(sf::RenderWindow& window) {
    window.draw(gameOverText);
    window.draw(winnerText);
    mainMenuButton.render(window);
}

void GameOver::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    mainMenuButton.handleEvent(event, window);
}