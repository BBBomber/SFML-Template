#include <SFML/Graphics.hpp>
#include "includes/Ball.h"
#include "includes/Paddle.h"

int main() {
    // Create a window with a resolution of 800x600 and title "Pong - PvP Mode"
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pong - PvP Mode");

    //setting max framerate
    window.setFramerateLimit(60);

    // Initialize two paddles for player 1 and player 2, and a ball
    Paddle player1(10, 250, sf::Keyboard::W, sf::Keyboard::S); // Player 1 uses W and S keys for movement
    Paddle player2(780, 250, sf::Keyboard::Up, sf::Keyboard::Down); // Player 2 uses Up and Down arrow keys
    Ball ball(400, 300); // Ball starts at the center of the screen

    sf::Clock clock; // Clock to keep track of time between frames for frame rate independence

    // Main game loop
    while (window.isOpen()) {
        sf::Event event;
        // Poll events to handle window closing and other events
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close(); // Close the window if the close button is clicked
            }
        }

        // Calculate the time elapsed since the last frame
        float deltaTime = clock.restart().asSeconds();

        // Update the paddles and ball based on the elapsed time
        player1.update(deltaTime);
        player2.update(deltaTime);
        ball.update(deltaTime);

        // Check for collisions between the ball and the paddles
        ball.checkCollision(player1);
        ball.checkCollision(player2);

        // Clear the window before drawing
        window.clear();
        // Draw the paddles and the ball on the window
        player1.render(window);
        player2.render(window);
        ball.render(window);
        // Display the contents of the window on the screen
        window.display();
    }

    return 0;
}
