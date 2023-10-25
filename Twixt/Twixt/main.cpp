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
    startButton.setOutlineColor(sf::Color::Black);
    startButton.setOutlineThickness(5);
    ///Declare the "Instructions" button
    sf::RectangleShape instructionButton(sf::Vector2f(200, 50));
    instructionButton.setFillColor(sf::Color::Red);
    instructionButton.setOutlineColor(sf::Color::Black);
    instructionButton.setOutlineThickness(5);
    instructionButton.setPosition(860, 650);

    // Declare the text for the "Start" button
    sf::Font font;
    font.loadFromFile("ARIAL.TTF");
    sf::Font titleFont;
    titleFont.loadFromFile("TitleText.ttf");
    sf::Text startButtonText("Play!", font, 24);
    startButtonText.setFillColor(sf::Color::Blue);
    // Center the text on the button
    startButtonText.setPosition(startButton.getPosition().x + (startButton.getSize().x - startButtonText.getGlobalBounds().width) / 2,
        startButton.getPosition().y + (startButton.getSize().y - startButtonText.getGlobalBounds().height) / 2);
    // Set the title of the window
    sf::Text titleText("Twixt Game", titleFont, 36); // You can adjust the font size
    titleText.setFillColor(sf::Color::Black); // Set the color
    titleText.setStyle(sf::Text::Bold); // Make it bold
    // Center the title above the button
    titleText.setPosition(860 + (startButton.getSize().x - titleText.getGlobalBounds().width) / 2,
        440);

  
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
        window.draw(titleText);
        window.draw(startButton);
        window.draw(instructionButton);
        window.draw(startButtonText);
     
        // Display what you have drawn
        window.display();
    }



    return 0;
}
