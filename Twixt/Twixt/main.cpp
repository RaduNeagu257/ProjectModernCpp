#include <SFML/Graphics.hpp>

//SFML sample code - try to run

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Twixt Game");
    window.setFramerateLimit(60);

    // Main game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Clear the window
        window.clear(sf::Color::White);

        // Draw your start menu options here

        // Display what you have drawn
        window.display();
    }

    return 0;
}
