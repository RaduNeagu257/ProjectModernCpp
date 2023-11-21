﻿#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include<iostream>
#include "Board.h"
#include "Pillar.h"
#include "Bridge.h"
float BRIDGE_LINE_THICKNESS = 5.0f;

bool IsPillarThere(const std::vector<Pillar>& pillars, const Pillar& tempPillar) {
    //each existing pillar is checked in case the new pillar would be placed on a position which already has a pillar on it
    for (const auto& pillar : pillars) {
        if (pillar.GetPosition() == tempPillar.GetPosition())
            return true;
    }
    return false;
}

//SFML sample code - try to run
int main() {
    sf::Clock clockAnimation;
    bool isAnimating = false; //for animation later on maybe

    Board board;
    // Open the window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Twixt Game");
    window.setFramerateLimit(60);
    bool isSelecting = false;
    sf::Vector2f startPosition;
    sf::Vector2f endPosition;
    Pillar startPillar;
    Pillar stopPillar;

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

    //Declare the text for the "ok" button
    sf::Font buttonFont;
    buttonFont.loadFromFile("ARIAL.TTF");
    sf::Text okButtonText("OK", buttonFont, 24);
    okButtonText.setFillColor(sf::Color::White);
    okButtonText.setPosition(okButton.getPosition().x + (okButton.getSize().x - okButtonText.getGlobalBounds().width) / 2,
        okButton.getPosition().y + (okButton.getSize().y - okButtonText.getGlobalBounds().height) / 2);


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
    titleText.setPosition(860 + (startButton.getSize().x - titleText.getGlobalBounds().width) / 2, 440);

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
                sf::Vector2f mousePositionFloat(mousePosition.x, mousePosition.y);

            
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
            int pillarAdded = 0;

            if (!boardWindow.isOpen()) {
                boardWindow.create(sf::VideoMode(1920, 1080), "Game Window", sf::Style::Close);
                boardWindow.setFramerateLimit(60);

            }
            std::vector<Pillar> redPillars, bluePillars;
            std::vector<Bridge> redBridges, blueBridges;
            
            sf::Color player = sf::Color::Red;
            while (boardWindow.isOpen()) {

                sf::Event boardEvent;
                boardWindow.clear(sf::Color::White);
                while (boardWindow.pollEvent(boardEvent)) {
                    if (boardEvent.type == sf::Event::Closed) {
                        boardWindow.close();
                        boardWindowOpen = false;
                    }
                    // Left mouse click is pressed to place a pillar
                    if (boardEvent.type == sf::Event::MouseButtonPressed && boardEvent.mouseButton.button == sf::Mouse::Left)
                    {
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
                            if (std::get<0>(tile).getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
                            {
                                //Create a new pillar and check its position before adding it to the vector
                                //std::cout << std::get<1>(tile) << " " << std::get<2>(tile) << "\n";
                                Pillar tempPillar(x * board.getTileSize(), y * board.getTileSize(), player, std::get<1>(tile),std::get<2>(tile));
                                tempPillar.setPosition(std::get<0>(tile).getPosition());
                                // Verificați dacă limita de piloni nu a fost atinsă
                                if (redPillars.size() < board.m_pillarNumberDef) {
                                    if (!IsPillarThere(redPillars, tempPillar)) {
                                        redPillars.push_back(tempPillar);
                                        std::cout << "Pillar added!" << std::endl;
                                    }
                                    else {
                                        std::cout << "Pillar already exists at this position!" << std::endl;
                                    }
                                }
                                else {
                                    std::cout << "Pillar limit reached!" << std::endl;
                                    sf::RenderWindow messageWindow(sf::VideoMode(300, 200), "Limita atinsa");
                                    sf::Text message;
                                    sf::Font font;
                                    if (!font.loadFromFile("Arial.TTF"));
                                    {
                                        std::cerr << "Nu s-a putut incarca fontul";
                                    }
                                    message.setFont(font);
                                    message.setString("Limita a fost atinsa");
                                    message.setCharacterSize(24);
                                    message.setFillColor(sf::Color::Red);
                                    message.setPosition(50, 80);
                                    while (messageWindow.isOpen()) {
                                        sf::Event event;
                                        while (messageWindow.pollEvent(event)) {
                                            if (event.type == sf::Event::Closed)
                                                messageWindow.close();
                                        }
                                        messageWindow.clear();
                                        messageWindow.draw(message);
                                        messageWindow.display();
                                    }
                                    boardWindow.close();
                                  
                                }
                               // if (redPillars.size() == board.m_pillarNumberDef) {
                                   /* sf::RenderWindow messageWindow(sf::VideoMode(300, 200), "Limita atinsa");
                                    sf::Text message;
                                    sf::Font font;
                                    if (!font.loadFromFile("Arial.TTF"));
                                    {
                                        std::cerr << "Nu s-a putut incarca fontul";
                                    }
                                    message.setFont(font);
                                    message.setString("Limita a fost atinsa");
                                    message.setCharacterSize(24);
                                    message.setFillColor(sf::Color::Red);
                                    message.setPosition(50, 80);
                                    while (messageWindow.isOpen()) {
                                        sf::Event event;
                                        while (messageWindow.pollEvent(event)) {
                                            if (event.type == sf::Event::Closed)
                                                messageWindow.close();
                                        }
                                        messageWindow.clear();
                                        messageWindow.draw(message);
                                        messageWindow.display();
                                    }
                                    boardWindow.close();*/
                                   /// boardWindowOpen = false;
                                    //break;
                            //}
                       
                    
                                if (player != sf::Color::Red) {
                                    board.SetPillarNumber(redPillars.size());
                                    player = sf::Color::Red;
                                }
                                else
                                {
                                    if (!IsPillarThere(redPillars, tempPillar)) {

                                        std::cout << "Pillar button clicked!" << std::endl; // debug message
                                        pillarAdded++;
                                        redPillars.push_back(tempPillar); //pillar is added to the vector of existing pillars
                                        // alternate between the red and black sides


                                        //aici
                                        if (!isSelecting)
                                        {
                                            startPillar = tempPillar;
                                            isSelecting = true;
                                        }
                                        else
                                        {
                                            isSelecting = false;
                                            stopPillar = tempPillar;

                                            //if (Bridge::canPlaceBridge(startPosition, endPosition, existingBridges))
                                            if (Bridge::canPlaceBridge(startPillar, stopPillar, redBridges))
                                            {
                                                std::cout << "Bridge Placed!\n";
                                                redBridges.emplace_back(startPillar, stopPillar, player);
                                                //existingBridges.emplace_back(startPosition, endPosition, sf::Color::Red);
                                            }
                                            else
                                                std::cout << "Can't place\n"<<startPillar.m_row<<" "<<startPillar.m_col<<"\n"<<stopPillar.m_row<<" "<<stopPillar.m_col<<"\n";
                                        }
                                    if (player == sf::Color::Red)
                                        player = sf::Color::Black;
                                    else
                                        player = sf::Color::Red;
                                    break;
                                    }
                                else
                                {
                                    std::cout << "There is already a pillar there!" << std::endl;
                                    break;
                                }

                                }
                                
                                
                            }


                        }

                    }

                }

                //boardWindow.clear(sf::Color::White);
                board.Draw(boardWindow);
                for (auto& pillar : redPillars)
                    pillar.Draw(boardWindow);
                for (const auto& bridge : redBridges) {
                    bridge.draw(boardWindow);
                }
                boardWindow.display();
            }
            std::cout << pillarAdded;//checks how many pillars we have(duplicate or unique pillars)
        }

        if (settingsWindowOpen) {
            sf::RectangleShape* selectedButtonShadow = nullptr;
            sf::RectangleShape* selectedButtonShadowPillars = nullptr;
            sf::RectangleShape* selectedButtonShadowBridges = nullptr;
            //Declare the "Back" button for the Settings Window


            sf::RectangleShape shadow;
            shadow.setFillColor(sf::Color(0, 0, 0, 100));

            sf::Font settingsFont;
            settingsFont.loadFromFile("ARIAL.TTF");
            sf::Text settingsText("Choose the dimensions of the board\n", settingsFont, 20);
            settingsText.setFillColor(sf::Color::Black);
            settingsText.setPosition(50, 40);

            sf::Text settingsText2("Choose the number of pillars\n", settingsFont, 20);
            settingsText2.setFillColor(sf::Color::Black);
            settingsText2.setPosition(450, 40);

            sf::Text settingsText3("Choose the number of bridges\n", settingsFont, 20);
            settingsText3.setFillColor(sf::Color::Black);
            settingsText3.setPosition(800, 40);

            if (!settingsWindow.isOpen()) {
                settingsWindow.create(sf::VideoMode(1100, 500), "Settings", sf::Style::Close);
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
                            std::cout << "OK button clicked in Settings!" << std::endl; 
                            settingsWindowOpen = false;
                           
                            settingsWindow.close(); 
                            window.clear();
                        }


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

                        // Check if the 28 pillars button was pressed
                        if (board.button28pillars.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
                        {
                            board.SetPillarNumber(board.m_pillarNumber1);
                            std::cout << "28 pillars button clicked!" << std::endl; // Debug message
                            selectedButtonShadowPillars = &board.button28pillars;
                        }
                       
                        // Check if the 50 pillars button was pressed
                        else if (board.button50pillars.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
                        {
                            board.SetPillarNumber(board.m_pillarNumber2);
                            std::cout << "50 pillars button clicked!" << std::endl; // Debug message
                            selectedButtonShadowPillars = &board.button50pillars;
                        }
                        // Check if the 78 pillars button was pressed
                        else if (board.button78pillars.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
                        {
                            board.SetPillarNumber(board.m_pillarNumber3);
                            std::cout << "78 pillars button clicked!" << std::endl; // Debug message
                            selectedButtonShadowPillars = &board.button78pillars;
                        }

                        // Check if the 25 bridges button was pressed
                        if (board.button25bridges.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
                        {
                            //board.SetBridgesNumber(board.m_bridgesNumber1);
                            std::cout << "25 bridges button clicked!" << std::endl; // Debug message
                            selectedButtonShadowBridges = &board.button25bridges;
                        }
                        // Check if the 50 bridges button was pressed
                        else if (board.button50bridges.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
                        {
                            //board.SetBridgesNumber(board.m_bridgesNumber2);
                            std::cout << "50 bridges button clicked!" << std::endl; // Debug message
                            selectedButtonShadowBridges = &board.button50bridges;
                        }
                        // Check if the 75 bridges button was pressed
                        else if (board.button75bridges.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
                        {
                           // board.SetBridgesNumber(board.m_bridgesNumber3);
                            std::cout << "75 bridges button clicked!" << std::endl; // Debug message
                            selectedButtonShadowBridges = &board.button75bridges;
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
                if (selectedButtonShadowPillars != nullptr)
                {
                    shadow.setPosition(selectedButtonShadowPillars->getPosition().x - 5, selectedButtonShadowPillars->getPosition().y - 5);
                    shadow.setSize(sf::Vector2f(selectedButtonShadowPillars->getSize().x + 10, selectedButtonShadowPillars->getSize().y + 10));
                    settingsWindow.draw(shadow);
                }
                if (selectedButtonShadowBridges != nullptr)
                {
                    shadow.setPosition(selectedButtonShadowBridges->getPosition().x - 5, selectedButtonShadowBridges->getPosition().y - 5);
                    shadow.setSize(sf::Vector2f(selectedButtonShadowBridges->getSize().x + 10, selectedButtonShadowBridges->getSize().y + 10));
                    settingsWindow.draw(shadow);
                }
                settingsWindow.draw(settingsText);
                settingsWindow.draw(settingsText2);
                settingsWindow.draw(settingsText3);
                settingsWindow.draw(okButton);
                settingsWindow.draw(okButtonText);

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
