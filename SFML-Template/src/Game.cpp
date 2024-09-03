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
    mainMenu(nullptr),  // Initialize pointer to null
    gameOverScreen(nullptr)  // Initialize pointer to null
{
    window.setFramerateLimit(60); // Set the frame rate limit

    if (!mainFont.loadFromFile(AssetPaths::mainFont)) {
        std::cerr << "Error loading font from " << AssetPaths::mainFont << std::endl;
        exit(EXIT_FAILURE); // Exit if the font cannot be loaded
    }

    // Load the scanline shader
    if (!scanlineShader.loadFromFile(AssetPaths::basicScanlineShader, sf::Shader::Fragment)) {
        std::cerr << "Failed to load scanline shader" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Initialize shader uniforms
    scanlineShader.setUniform("resolution", sf::Glsl::Vec2(windowSize.x, windowSize.y));

    // Now that the font is loaded, initialize the main menu
    mainMenu = new MainMenu(mainFont, gameState);

    gameOverScreen = new GameOver(mainFont, gameState);

    // Initialize the middle line
    middleLine.setSize(sf::Vector2f(2.0f, static_cast<float>(windowSize.y)));
    middleLine.setPosition(windowSize.x / 2.0f, 0.0f);
    middleLine.setFillColor(sf::Color::White);

    // Initialize the score texts
    initializeScoreText();

    //updateScore(); // Initial score update
}


// Destructor to clean up the MainMenu pointer
Game::~Game() {
    delete mainMenu;
    delete gameOverScreen;
    
}

void Game::initializeScoreText() {
    player1ScoreText.setFont(mainFont);
    player1ScoreText.setCharacterSize(36);
    player1ScoreText.setFillColor(sf::Color::White);
    player1ScoreText.setPosition(200.0f, 20.0f); // Position on the left side

    player2ScoreText.setFont(mainFont);
    player2ScoreText.setCharacterSize(36);
    player2ScoreText.setFillColor(sf::Color::White);
    player2ScoreText.setPosition(600.0f, 20.0f); // Position on the right side
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

        // Handle window resizing
        if (event.type == sf::Event::Resized) {
            sf::Vector2u newSize = window.getSize();
            windowSize.x = newSize.x;
            windowSize.y = newSize.y;

            //// Update the viewport to the new window size
            //sf::FloatRect visibleArea(0, 0, newSize.x, newSize.y);
            //window.setView(sf::View(visibleArea));

            // Update the shader's resolution uniform with the new size
            scanlineShader.setUniform("resolution", sf::Glsl::Vec2(newSize.x, newSize.y));
        }

        if (gameState == GameState::MainMenu && mainMenu) {
            mainMenu->handleEvent(event, window);
        }
        else if (gameState == GameState::GameOver && gameOverScreen) {
            gameOverScreen->handleEvent(event, window);
        }
    }
}

// Updates the positions and states of the paddles and ball
void Game::update(float deltaTime) {

    if (gameState == GameState::PlayingPvP) {
        player1.update(deltaTime);
        player2.update(deltaTime);
    }
    else if (gameState == GameState::PlayingVsAI) {
        player1.update(deltaTime);  // Player controls the left paddle
        player2.updateAI(deltaTime, ball, windowSize.x);  // AI controls the right paddle
    }

    if (gameState == GameState::PlayingPvP || gameState == GameState::PlayingVsAI)
    {
        ball.update(deltaTime);

        // Check for collisions between the ball and the paddles
        ball.checkCollision(player1, audioManager);
        ball.checkCollision(player2, audioManager);

        // Update score based on ball position
        updateScore();
    }
    

}

// Renders the paddles and the ball on the window
void Game::render() {
    window.clear(sf::Color(128, 128, 128, 255)); // Clear the window

    if (gameState == GameState::MainMenu && mainMenu) {
        mainMenu->render(window); // Render the main menu
    }
    else if (gameState == GameState::PlayingPvP || gameState == GameState::PlayingVsAI) {
        drawMiddleLine(); // Draw the middle line
        player1.render(window);    // Draw player 1's paddle
        player2.render(window);    // Draw player 2's paddle
        ball.render(window);       // Draw the ball
        window.draw(player1ScoreText); // Draw player 1's score
        window.draw(player2ScoreText); // Draw player 2's score
    }
    else if (gameState == GameState::GameOver && gameOverScreen) {
        gameOverScreen->render(window);
    }

    sf::Texture windowTexture;
    windowTexture.create(window.getSize().x, window.getSize().y);
    windowTexture.update(window);

    // Create a sprite from the captured texture
    sf::Sprite sprite(windowTexture);

    // Set shader uniforms
    scanlineShader.setUniform("resolution", sf::Glsl::Vec2(windowSize.x, windowSize.y));
    scanlineShader.setUniform("time", clock.getElapsedTime().asSeconds());
    scanlineShader.setUniform("texture", windowTexture);

    window.draw(sprite, &scanlineShader);

    window.display(); // Display the contents of the window on the screen
}

// Updates the score based on the ball's position
void Game::updateScore() {
    if (ball.getBounds().left < 0) {
        // Ball is out of bounds on player 1's side
        player2Score++;
        resetPositions();
    }
    else if (ball.getBounds().left + ball.getBounds().width > windowSize.x) {
        // Ball is out of bounds on player 2's side
        player1Score++;
        resetPositions();
    }

    // Update the score text
    player1ScoreText.setString(std::to_string(player1Score));
    player2ScoreText.setString(std::to_string(player2Score));

    if (player1Score >= 5 || player2Score >= 5) {
        gameState = GameState::GameOver;
        gameOverScreen->setWinner(player1Score >= 5 ? 1 : 2);
        resetPositions();
        resetScores();
                
    }
}

void Game::resetScores()
{
    player1Score = 0;
    player2Score = 0;
}

// Resets the positions of the ball and paddles
void Game::resetPositions() {
    ball.reset(); // Reset the ball to the center
    player1.setPosition(player1Position); // Reset player 1's position
    player2.setPosition(player2Position); // Reset player 2's position
}

// Draws the middle line on the screen
void Game::drawMiddleLine() {
    window.draw(middleLine);
}
