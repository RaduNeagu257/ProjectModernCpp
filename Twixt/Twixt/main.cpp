#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include<iostream>
#include "Board.h"
#include "Pillar.h"

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

    // Declare the "Settings" button
    sf::RectangleShape settingsButton(sf::Vector2f(200, 50));
    settingsButton.setFillColor(sf::Color::Green);
    settingsButton.setPosition(860, 570);
    settingsButton.setOutlineColor(sf::Color::Black);
    settingsButton.setOutlineThickness(5);
    //Declare the "Ok' button
    sf::RectangleShape okButton(sf::Vector2f(200, 50));
    okButton.setFillColor(sf::Color::Blue); 
    okButton.setPosition(50, 300); 
    okButton.setOutlineColor(sf::Color::Black);
    okButton.setOutlineThickness(5);

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

    // Declare the text for the "Settings" button
    sf::Font settingsFont;
    settingsFont.loadFromFile("ARIAL.TTF");
    sf::Font settingsTitleFont;
    settingsTitleFont.loadFromFile("TitleText.ttf");
    sf::Text settingsButtonText("Settings", font, 24);
    settingsButtonText.setFillColor(sf::Color::Black);
    // Center the text on the button
    settingsButtonText.setPosition(settingsButton.getPosition().x + (settingsButton.getSize().x - settingsButtonText.getGlobalBounds().width) / 2,
        settingsButton.getPosition().y + (settingsButton.getSize().y - settingsButtonText.getGlobalBounds().height) / 2);


    // Set the title of the window
    sf::Text titleText("Twixt Game", titleFont, 36); // You can adjust the font size
    titleText.setFillColor(sf::Color::Black); // Set the color
    titleText.setStyle(sf::Text::Bold); // Make it bold
    // Center the title above the button
    titleText.setPosition(860 + (startButton.getSize().x - titleText.getGlobalBounds().width) / 2,
        440);

    bool instructionsWindowOpen = false;
    bool boardWindowOpen = false;
    bool settingsWindowOpen = false;
    sf::RenderWindow instructionsWindow;
    sf::RenderWindow settingsWindow;
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
                //Check if the "Settings" button is clicked
                else  if (settingsButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
                    settingsWindowOpen = true;
                    std::cout << "Settings button clicked!" << std::endl; // Debug message
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
                "6. Add or remove as many legal links between pegs of your color as you wish. A link is legal when \n the two pegs are at opposite corners of a six-hole rectangle (like a knight's move in chess), and \n no other link crosses the linking path, not even one of your own.\n"
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
            std::vector<Pillar> pillars;
            while (boardWindow.isOpen()) {
                
                sf::Event boardEvent;
                boardWindow.clear(sf::Color::White);
                while (boardWindow.pollEvent(boardEvent)) {
                    if (boardEvent.type == sf::Event::Closed) {
                        boardWindow.close();
                        boardWindowOpen = false;
                    }
                    if (boardEvent.type == sf::Event::MouseButtonPressed && boardEvent.mouseButton.button == sf::Mouse::Left)
                    {
                        
                        //Place pillar on board

                        sf::Vector2f mousePositionFloat;
                        sf::Vector2i mousePosition;
                        mousePosition = sf::Mouse::getPosition(boardWindow);
                        for (auto& tile : board.getTiles())
                        {
                            // Convert the mousePosition to a sf::Vector2f object.
                            mousePositionFloat = sf::Vector2f(mousePosition.x, mousePosition.y);

                            // Check if the mouse is over a cell.
                            int x = mousePositionFloat.x / board.getTileSize();
                            int y = mousePositionFloat.y / board.getTileSize();
                            if (tile.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
                            {
                                std::cout << "Pillar button clicked!" << std::endl; // Debug message
                                // Create a new pillar.
                                Pillar pillar(x * board.getTileSize(), y * board.getTileSize(), sf::Color::Red);
                                pillar.setPosition(tile.getPosition());
                                pillars.push_back(pillar);
                                break;
                            }
                            
                        }
                        
                    }
                    
                }
                
                //boardWindow.clear(sf::Color::White);
                board.Draw(boardWindow);
                for(auto& pillar:pillars)
                    pillar.Draw(boardWindow);
                boardWindow.display();
            }
        }
        
        if (settingsWindowOpen) {
            sf::RectangleShape* selectedButtonShadow = nullptr;
            //Declare the "Back" button for the Settings Window
         

            sf::RectangleShape shadow;
            shadow.setFillColor(sf::Color(0, 0, 0, 100));

            sf::Font settingsFont;
            settingsFont.loadFromFile("ARIAL.TTF");
            sf::Text settingsText("Choose the dimensions of the board\n", settingsFont, 20);
            settingsText.setFillColor(sf::Color::Black);
            settingsText.setPosition(50, 40);

            if (!settingsWindow.isOpen()) {
                settingsWindow.create(sf::VideoMode(1000, 500), "Settings", sf::Style::Close);
                settingsWindow.setFramerateLimit(60);
          
            }
            while (settingsWindow.isOpen()) {
                sf::Event settingsEvent;
                while (settingsWindow.pollEvent(settingsEvent)) {
                    if (settingsEvent.type == sf::Event::Closed) {
                        settingsWindow.close();
                        settingsWindowOpen = false;
                    }
                    if (settingsEvent.type == sf::Event::MouseButtonPressed && settingsEvent.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2i mousePosition = sf::Mouse::getPosition(settingsWindow);
                        if (okButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
                            // Aici puteți adăuga logica sau acțiunile corespunzătoare atunci când butonul "OK" este apăsat în fereastra de setări.
                            std::cout << "OK button clicked in Settings!" << std::endl; // Mesaj de depanare
                        }
                        // Verificați dacă alte evenimente din fereastra de setări sunt gestionate aici.
                    }

                    if (settingsEvent.type == sf::Event::MouseButtonPressed && settingsEvent.mouseButton.button == sf::Mouse::Left)
                    {
                        sf::Vector2i mousePosition = sf::Mouse::getPosition(settingsWindow);

                        // Check if the 18x18 button was pressed
                        if (board.button18x18.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
                        {
                            board.SetBoardSize(board.m_boardSize1);
                            std::cout << "18x18 button clicked!" << std::endl; // Debug message
                            selectedButtonShadow = &board.button18x18;
                        }
                        // Check if the 24x24 button was pressed
                        else if (board.button24x24.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
                        {
                            board.SetBoardSize(board.m_boardSize2);
                            std::cout << "24x24 button clicked!" << std::endl; // Debug message
                            selectedButtonShadow = &board.button24x24;
                        }
                        // Check if the 30x30button was pressed
                        else if (board.button30x30.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
                        {
                            board.SetBoardSize(board.m_boardSize3);
                            std::cout << "30x30 button clicked!" << std::endl; // Debug message
                            selectedButtonShadow = &board.button30x30;
                        }
                    }
                }
                settingsWindow.clear(sf::Color::Red);
                if (selectedButtonShadow != nullptr)
                {
                    shadow.setPosition(selectedButtonShadow->getPosition().x - 5, selectedButtonShadow->getPosition().y - 5);
                    shadow.setSize(sf::Vector2f(selectedButtonShadow->getSize().x + 10, selectedButtonShadow->getSize().y + 10));
                    settingsWindow.draw(shadow);
                }
                settingsWindow.draw(settingsText);
                settingsWindow.draw(okButton);

                board.DrawSettingsButtons(settingsWindow);
                
                settingsWindow.display();
           
            }
        }

        // Clear the window
        window.clear(sf::Color::White);

        // Add button
        window.draw(titleText);
        window.draw(startButton);
        window.draw(instructionButton);
        window.draw(settingsButton);
        window.draw(startButtonText);
        window.draw(instructionsButtonText);
        window.draw(settingsButtonText);
      //  window.draw(okButton);

        // Display what you have drawn
        window.display();
    }


    return 0;
}
