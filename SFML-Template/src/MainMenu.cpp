#include "../includes/MainMenu.h"
#include <iostream>

MainMenu::MainMenu(const sf::Font& font, GameState& gameState)
    : gameState(gameState) {
    buttons.push_back(Button(font, "PvP", 300.0f, 200.0f, 200.0f, 50.0f, sf::Color::Blue, sf::Color::White, sf::Color::Yellow, 2.0f, std::bind(&MainMenu::onPlayerVsPlayerClicked, this)));
    buttons.push_back(Button(font, "Vs AI", 300.0f, 300.0f, 200.0f, 50.0f, sf::Color::Green, sf::Color::White, sf::Color::Yellow, 2.0f, std::bind(&MainMenu::onVsAiClicked, this)));
    buttons.push_back(Button(font, "Quit", 300.0f, 400.0f, 200.0f, 50.0f, sf::Color::Red, sf::Color::White, sf::Color::Yellow, 2.0f, std::bind(&MainMenu::onQuitClicked, this)));
}

void MainMenu::onPlayerVsPlayerClicked() {
    gameState = GameState::PlayingPvP;
}

void MainMenu::onVsAiClicked() {
    std::cout << "Vs AI Button Clicked!" << std::endl;
}

void MainMenu::onQuitClicked() {
    std::cout << "Quit Button Clicked!" << std::endl;
    exit(0);
}

void MainMenu::render(sf::RenderWindow& window) {
    for (auto& button : buttons) {
        button.render(window);
    }
}

void MainMenu::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    for (auto& button : buttons) {
        button.handleEvent(event, window);
    }
}
