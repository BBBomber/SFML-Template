#include "../includes/Game.h"
#include "../includes/AssetPaths.h"
#include <iostream>

// Constructor initializes the game objects and sets the initial game state
Game::Game()
    : window(sf::VideoMode(windowSize.x, windowSize.y), windowTitle),
    player1(player1Position.x, player1Position.y, sf::Keyboard::W, sf::Keyboard::S),
    player2(player2Position.x, player2Position.y, sf::Keyboard::Up, sf::Keyboard::Down),
    ball(ballPosition.x, ballPosition.y),
    gameState(GameState::MainMenu),  // Start in the main menu state
    mainMenu(nullptr)  // Initialize pointer to null
{
    window.setFramerateLimit(60); // Set the frame rate limit

    if (!mainFont.loadFromFile(AssetPaths::mainFont)) {
        std::cerr << "Error loading font from " << AssetPaths::mainFont << std::endl;
        exit(EXIT_FAILURE); // Exit if the font cannot be loaded
    }

    // Now that the font is loaded, initialize the main menu
    mainMenu = new MainMenu(mainFont, gameState);

    // Initialize the middle line
    middleLine.setSize(sf::Vector2f(2.0f, static_cast<float>(windowSize.y)));
    middleLine.setPosition(windowSize.x / 2.0f, 0.0f);
    middleLine.setFillColor(sf::Color::White);
}


// Destructor to clean up the MainMenu pointer
Game::~Game() {
    delete mainMenu;
}

// The main game loop, which keeps the window open and updates the game state
void Game::run() {
    while (window.isOpen()) {
        processEvents();           // Handle input and window events
        update(clock.restart().asSeconds()); // Update game objects based on time
        render();                  // Render the game objects
    }
}

// Handles input and window events, like closing the window
void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close(); // Close the window if the close button is clicked
        }

        if (gameState == GameState::MainMenu && mainMenu) {
            mainMenu->handleEvent(event, window);
        }
    }
}

// Updates the positions and states of the paddles and ball
void Game::update(float deltaTime) {
    player1.update(deltaTime);
    player2.update(deltaTime);
    ball.update(deltaTime);

    // Check for collisions between the ball and the paddles
    ball.checkCollision(player1, audioManager);
    ball.checkCollision(player2, audioManager);
}

// Renders the paddles and the ball on the window
void Game::render() {
    window.clear(); // Clear the window

    if (gameState == GameState::MainMenu && mainMenu) {
        mainMenu->render(window); // Render the main menu
    }
    else if (gameState == GameState::PlayingPvP || gameState == GameState::PlayingVsAI) {
        drawMiddleLine(); // Draw the middle line
        player1.render(window);    // Draw player 1's paddle
        player2.render(window);    // Draw player 2's paddle
        ball.render(window);       // Draw the ball
    }

    window.display(); // Display the contents of the window on the screen
}

// Draws the middle line on the screen
void Game::drawMiddleLine() {
    window.draw(middleLine);
}
