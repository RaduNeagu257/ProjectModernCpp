#include <SFML/Graphics.hpp>

//SFML sample code - try to run

int main() {
    // Open the window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Twixt Game");
    window.setFramerateLimit(60);

    // Declare the "Start" button
    sf::RectangleShape startButton(sf::Vector2f(200, 50));
    startButton.setFillColor(sf::Color::Cyan);
    startButton.setPosition(860, 490);

    // Declare the text for the "Start" button
    sf::Font font;
    font.loadFromFile("ARIAL.TTF");
    sf::Text startButtonText("Play!", font, 24);
    startButtonText.setFillColor(sf::Color::Blue);
    // Center the text on the button
    startButtonText.setPosition(startButton.getPosition().x + (startButton.getSize().x - startButtonText.getGlobalBounds().width) / 2,
        startButton.getPosition().y + (startButton.getSize().y - startButtonText.getGlobalBounds().height) / 2);
 
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

        // Add button
        window.draw(startButton);
        window.draw(startButtonText);

        // Display what you have drawn
        window.display();
    }

    return 0;
}
