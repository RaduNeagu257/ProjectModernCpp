#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include<iostream>

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


    // Declare the text for the "Instructions" button
    sf::Font instructionsFont;
    instructionsFont.loadFromFile("ARIAL.TTF");
    sf::Font instructionsTitleFont;
    instructionsTitleFont.loadFromFile("TitleText.ttf");
    sf::Text instructionsButtonText("Instructions", font, 24);
    instructionsButtonText.setFillColor(sf::Color::Black);


    // Center the text on the button
    instructionsButtonText.setPosition(instructionButton.getPosition().x + (instructionButton.getSize().x - instructionsButtonText.getGlobalBounds().width) / 2,
        instructionButton.getPosition().y + (instructionButton.getSize().y - instructionsButtonText.getGlobalBounds().height) / 2);

    // Set the title of the window
    sf::Text titleText("Twixt Game", titleFont, 36); // You can adjust the font size
    titleText.setFillColor(sf::Color::Black); // Set the color
    titleText.setStyle(sf::Text::Bold); // Make it bold
    // Center the title above the button
    titleText.setPosition(860 + (startButton.getSize().x - titleText.getGlobalBounds().width) / 2,
        440);

    bool instructionsWindowOpen = false;
    sf::RenderWindow instructionsWindow;

  
    // Main game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // Check if the "Instructions" button is clicked
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                if (instructionButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
                    instructionsWindowOpen = true;
                    std::cout << "Instructions button clicked!" << std::endl; // Debug message
                }
            }
        
        }
        if (instructionsWindowOpen) {
            if (!instructionsWindow.isOpen()) {
                instructionsWindow.create(sf::VideoMode(800, 600), "Instructions", sf::Style::Close);
                instructionsWindow.setFramerateLimit(60);
            }

            sf::Event instructionsEvent;
            while (instructionsWindow.pollEvent(instructionsEvent)) {
                if (instructionsEvent.type == sf::Event::Closed) {
                    instructionsWindow.close();
                    instructionsWindowOpen = false;
                }
            }

            instructionsWindow.clear(sf::Color::White);
           
            instructionsWindow.display();
        }
        // Clear the window
        window.clear(sf::Color::White);

        // Add button
        window.draw(titleText);
        window.draw(startButton);
        window.draw(instructionButton);
        window.draw(startButtonText);
        window.draw(instructionsButtonText);
     
        // Display what you have drawn
        window.display();
    }

   
    return 0;
}

    