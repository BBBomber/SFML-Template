#include "../includes/MainMenu.h"
#include <iostream>

MainMenu::MainMenu(const sf::Font& font, GameState& gameState)
    : gameState(gameState) {
    initializeBackground();
    initializeTitle(font);
    initializeButtons(font);
}

void MainMenu::initializeBackground() {
    // Load the background texture
    if (!backgroundTexture.loadFromFile(AssetPaths::bgImage)) {
        std::cerr << "Error loading background image from " << AssetPaths::bgImage << std::endl;
        exit(EXIT_FAILURE); // Exit if the background image cannot be loaded
    }

    // Set up the background sprite
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(800) / backgroundTexture.getSize().x,
        static_cast<float>(600) / backgroundTexture.getSize().y
    );
}

void MainMenu::initializeTitle(const sf::Font& font) {
    // Set up the title text
    titleText.setFont(font);
    titleText.setString("PONG");
    titleText.setCharacterSize(72);  // Big size
    titleText.setStyle(sf::Text::Bold);
    titleText.setFillColor(sf::Color::White);
    titleText.setOutlineColor(sf::Color::Black);  // Outline color
    titleText.setOutlineThickness(5.0f);          // Outline thickness
    titleText.setPosition(
        (800.0f - titleText.getLocalBounds().width) / 2.0f, // Center horizontally
        50.0f // Top padding
    );
}

void MainMenu::initializeButtons(const sf::Font& font) {
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

    window.draw(backgroundSprite);

    window.draw(titleText);

    for (auto& button : buttons) {
        button.render(window);
    }
}

void MainMenu::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    for (auto& button : buttons) {
        button.handleEvent(event, window);
    }
}
