#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include<iostream>
#include "Board.h"
#include"Pillars.h"
//SFML sample code - try to run

int main() {

    Board board;

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
    bool boardWindowOpen = false;
    sf::RenderWindow instructionsWindow;
    sf::RenderWindow boardWindow;


    // Main game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // Check if the left mouse click is pressed
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                // Check if the "Instructions" button is clicked
                if (instructionButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
                    instructionsWindowOpen = true;
                    std::cout << "Instructions button clicked!" << std::endl; // Debug message
                }
                // Check if the "Board game" button is clicked
                else if (startButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
                    boardWindowOpen = true;
                    std::cout << "Board Game button clicked!" << std::endl; //Debug message
                }
            }

        }
        if (instructionsWindowOpen) {
            if (!instructionsWindow.isOpen()) {
                instructionsWindow.create(sf::VideoMode(1000, 500), "Instructions", sf::Style::Close);
                instructionsWindow.setFramerateLimit(60);
            }

            sf::Event instructionsEvent;
            while (instructionsWindow.pollEvent(instructionsEvent)) {
                if (instructionsEvent.type == sf::Event::Closed) {
                    instructionsWindow.close();
                    instructionsWindowOpen = false;
                }
            }
            instructionsWindow.clear(sf::Color::Cyan);
            sf::Font instructions2Font;
            instructions2Font.loadFromFile("ARIAL.TTF");
            sf::Text instructions2Text("Welcome to the Twixt Game!\n"
                "\n"
                "Here are the rules of the game: \n"
                "\n"
                "1. You take turns placing pegs of your respective colors on the board, one peg per turn.\n"
                "2. The player with the red color makes the first move.\n"
                "3. You may not place a peg on your opponent's border rows.\n"
                "4. After the first peg is placed, the second player has the option to swap sides. (If the second player \n chooses not to swap immediately after the first peg is placed, then sides may not be swapped \n later in that game.\n"
                "6. Add or remove as many legal links between pegs of your color as you wish. A link is legal when \n the two pegs are at opposite corners of a six-hole rectangle (like a knight's move in chess), and \n no other link crosses the linking  path, not even one of your own.\n"
                "\n"
                "Your goal is to connect a peg in one of your border rows to a peg in your other border row, with a \n continuous chain of linked pegs. If neither side can achieve this, the game is a draw.\n",

                instructions2Font, 20);
            instructions2Text.setFillColor(sf::Color::Black);
            instructions2Text.setPosition(50, 50);
            instructionsWindow.draw(instructions2Text);


            instructionsWindow.display();
        }

        if (boardWindowOpen) {
            if (!boardWindow.isOpen()) {
                boardWindow.create(sf::VideoMode(1920, 1080), "Game Window", sf::Style::Close);
                boardWindow.setFramerateLimit(60);
            }
            sf::Event boardEvent;
            while (boardWindow.pollEvent(boardEvent)) {
                if (boardEvent.type == sf::Event::Closed) {
                    boardWindow.close();
                    boardWindowOpen = false;
                }
            }
            boardWindow.clear(sf::Color::White);
            board.Draw(boardWindow);
            boardWindow.display();
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