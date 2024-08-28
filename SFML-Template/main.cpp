#include <SFML/Graphics.hpp>

int main()
{
    // Create a window with the title "SFML-Template"
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML-Template");

    // Main loop that continues until the window is closed
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the window with a black color, classy.
        window.clear(sf::Color::Black);

        // Display the contents of the window on the screen
        window.display();
    }

    return 0;
}
