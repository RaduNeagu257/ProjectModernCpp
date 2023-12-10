#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include<iostream>
#include "Board.h"
#include "Pillar.h"
#include "Bridge.h"
float BRIDGE_LINE_THICKNESS = 5.0f;

//SFML sample code - try to run
U8 main() {
   
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
    bool closeMessageWindowClicked = false;

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
            U16 pillarAdded = 0;

            if (!boardWindow.isOpen()) {
                boardWindow.create(sf::VideoMode(1920, 1080), "Game Window", sf::Style::Close);
                boardWindow.setFramerateLimit(60);

            }
            std::vector<Pillar> redPillars, blackPillars;
            std::vector<Bridge> redBridges, blackBridges;
            
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
                            U8 x = mousePositionFloat.x / board.getTileSize();
                            U8 y = mousePositionFloat.y / board.getTileSize();
                            if (std::get<0>(tile).getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
                            {
                                //Create a new pillar and check its position before adding it to the vector
                                Pillar tempPillar(x * board.getTileSize(), y * board.getTileSize(), player, std::get<1>(tile), std::get<2>(tile));
                                tempPillar.SetPosition(std::get<0>(tile).getPosition());
                                  if (player == sf::Color::Red) // Red side's turn
                                  {

                                         
                                      if (redPillars.size() < board.GetMaxPillarNumber())
                                        {

                                            if (board.PlacePillarInBase(tempPillar)){
                                                if (!board.IsPillarThere(redPillars, tempPillar) && !board.IsPillarThere(blackPillars, tempPillar))
                                                {
                                                    std::cout << "Red ";
                                                    Board::PlacePillar(board, redPillars, tempPillar, player, pillarAdded);
                                                    board.PlaceBridge(tempPillar, redPillars, redBridges, player);
                                                    player = sf::Color::Black;
                                                    
                                                }
                                                else
                                                    std::cout << "There is already a pillar there.\n";

                                            }
                                            else {
                                                std::cout << "error in base" << std::endl;
                                                sf::RenderWindow errorMessageWindow(sf::VideoMode(500, 200), "Error: Wrong Base");
                                                sf::Text errorMessage;
                                                sf::Font font;
                                                font.loadFromFile("ARIAL.TTF");
                                                errorMessage.setFont(font);
                                                errorMessage.setString("Error: Pillar placed in wrong base!");
                                                errorMessage.setCharacterSize(24);
                                                errorMessage.setFillColor(sf::Color::Red);
                                                sf::FloatRect messageRect = errorMessage.getLocalBounds();
                                                errorMessage.setOrigin(messageRect.left + messageRect.width / 2.0f, messageRect.top + messageRect.height / 2.0f);
                                                errorMessage.setPosition(errorMessageWindow.getView().getCenter());

                                                while (errorMessageWindow.isOpen()) {
                                                    sf::Event event;
                                                    while (errorMessageWindow.pollEvent(event)) {
                                                        if (event.type == sf::Event::Closed)
                                                            errorMessageWindow.close();
                                                    }

                                                    errorMessageWindow.clear();
                                                    errorMessageWindow.draw(errorMessage);
                                                    errorMessageWindow.display();
                                                }
                                            }
                                        }
                                        else
                                        {
                                            std::cout << "Pillar limit reached!" << std::endl;
                                            sf::RenderWindow messageWindow(sf::VideoMode(500, 300), "Limit reached");
                                            sf::Text message;
                                            sf::Font font;
                                            sf::RectangleShape closeButton(sf::Vector2f(70, 30));
                                            closeButton.setFillColor(sf::Color::Red);
                                            closeButton.setPosition(350, 240); // Position the button within the messageWindow
                                            sf::Text closeButtonText("Close", font, 18);
                                            closeButtonText.setFillColor(sf::Color::Blue);
                                            closeButtonText.setPosition(closeButton.getPosition() + sf::Vector2f(10, 10)); // Position the text on the button

                                            font.loadFromFile("ARIAL.TTF");
                                            message.setFont(font);
                                            message.setString("Limit of pillars reached");
                                            message.setCharacterSize(24);
                                            message.setFillColor(sf::Color::Red);

                                            sf::FloatRect messageRect = message.getLocalBounds();
                                            message.setOrigin(messageRect.left + messageRect.width / 2.0f, messageRect.top + messageRect.height / 2.0f);
                                            message.setPosition(messageWindow.getView().getCenter());

                                            while (messageWindow.isOpen()) {
                                                sf::Event event;
                                                while (messageWindow.pollEvent(event)) {
                                                    if (event.type == sf::Event::Closed)
                                                        messageWindow.close();
                                                    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                                                        sf::Vector2i mousePos = sf::Mouse::getPosition(messageWindow);
                                                        if (closeButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                                                            std::cout << "Close button clicked. Closing message window." << std::endl;
                                                            closeMessageWindowClicked = true;
                                                            messageWindow.close(); // Close the message window
                                                        }
                                                    }
                                                }
                                                if (closeMessageWindowClicked) {
                                                    boardWindow.close(); // Închide fereastra de joc
                                                    boardWindowOpen = false; // Setează starea ferestrei de joc pe închis
                                                    window.create(sf::VideoMode(1920, 1080), "Twixt Game Menu"); // Recreează fereastra de meniu
                                                    closeMessageWindowClicked = false; // Reset the flag
                                                }
                                                messageWindow.clear();
                                                messageWindow.draw(message);
                                                messageWindow.draw(closeButton);
                                                messageWindow.draw(closeButtonText);
                                                messageWindow.display();

                                            }
                                            boardWindow.close();
                                            break;

                                        }
                                      
                                        break;
                                    }
                                    else // Black side's turn
                                    {
                                        if (blackPillars.size() < board.GetMaxPillarNumber())
                                        {
                                            if (board.PlacePillarInBase(tempPillar)) {
                                                if (!board.IsPillarThere(blackPillars, tempPillar) && !board.IsPillarThere(redPillars, tempPillar))
                                                {
                                                    std::cout << "Black ";
                                                    Board::PlacePillar(board, blackPillars, tempPillar, player, pillarAdded);
                                                    board.PlaceBridge(tempPillar, blackPillars, blackBridges, player);
                                                    player = sf::Color::Red;
                                                }
                                                else
                                                    std::cout << "There is already a pillar there.\n";
                                            }
                                            else {
                                                std::cout << "error in base" << std::endl;
                                                sf::RenderWindow errorMessageWindow(sf::VideoMode(500, 200), "Error: Wrong Base");
                                                sf::Text errorMessage;
                                                sf::Font font;
                                                font.loadFromFile("ARIAL.TTF");
                                                errorMessage.setFont(font);
                                                errorMessage.setString("Error: Pillar placed in wrong base!");
                                                errorMessage.setCharacterSize(24);
                                                errorMessage.setFillColor(sf::Color::Red);
                                                sf::FloatRect messageRect = errorMessage.getLocalBounds();
                                                errorMessage.setOrigin(messageRect.left + messageRect.width / 2.0f, messageRect.top + messageRect.height / 2.0f);
                                                errorMessage.setPosition(errorMessageWindow.getView().getCenter());

                                                while (errorMessageWindow.isOpen()) {
                                                    sf::Event event;
                                                    while (errorMessageWindow.pollEvent(event)) {
                                                        if (event.type == sf::Event::Closed)
                                                            errorMessageWindow.close();
                                                    }

                                                    errorMessageWindow.clear();
                                                    errorMessageWindow.draw(errorMessage);
                                                    errorMessageWindow.display();
                                                }
                                            }
                                            
                                            if (blackPillars.size() == redPillars.size() && pillarAdded == 2) //Allow the black side to choose to swap sides after the first turn
                                            {
                                                //declare variables for window, window text, buttons and buttons text
                                                sf::RenderWindow messageWindow(sf::VideoMode(500, 200), "Swap sides");
                                                sf::Text text;
                                                sf::Font font;
                                                sf::RectangleShape yesButton(sf::Vector2f(75, 50));
                                                sf::RectangleShape noButton(sf::Vector2f(75, 50));

                                                //setting up buttons
                                                yesButton.setFillColor(sf::Color::Red);
                                                noButton.setFillColor(sf::Color::Red);
                                                yesButton.setPosition(175, 150);
                                                noButton.setPosition(250, 150);
                                                sf::Text yesButtonText("Yes", font, 24);
                                                sf::Text noButtonText("No", font, 24);
                                                yesButtonText.setFillColor(sf::Color::Blue);
                                                noButtonText.setFillColor(sf::Color::Blue);

                                                sf::FloatRect textRect = yesButtonText.getLocalBounds();

                                                // Position the text relative to the button

                                                yesButtonText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
                                                yesButtonText.setPosition(sf::Vector2f(yesButton.getPosition().x + yesButton.getSize().x / 2.0f, yesButton.getPosition().y + yesButton.getSize().y / 2.0f));

                                                noButtonText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
                                                noButtonText.setPosition(sf::Vector2f(noButton.getPosition().x + noButton.getSize().x / 2.0f, noButton.getPosition().y + noButton.getSize().y / 2.0f));


                                                //setting up text on the window
                                                font.loadFromFile("ARIAL.TTF");
                                                text.setFont(font);
                                                text.setString("Do you want to swap sides?");
                                                text.setCharacterSize(24);
                                                text.setFillColor(sf::Color::Red);

                                                //setting up text on the window
                                                textRect = text.getLocalBounds();
                                                text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
                                                text.setPosition(messageWindow.getView().getCenter());



                                                while (messageWindow.isOpen())
                                                {
                                                    sf::Event event;
                                                    while (messageWindow.pollEvent(event))
                                                    {
                                                        if (event.type == sf::Event::Closed)
                                                            messageWindow.close();
                                                        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                                                            sf::Vector2i mousePos = sf::Mouse::getPosition(messageWindow);
                                                            if (yesButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                                                                std::cout << "\"Yes\" button clicked. Sides are swapped. Closing message window." << std::endl;
                                                                // Swap the pillars and the drawn vertical/horizontal lines
                                                                Board::SwapSides(redPillars, blackPillars);
                                                                board.SwapLines();
                                                                messageWindow.close(); // Close the message window
                                                            }
                                                            else if (noButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                                                            {
                                                                std::cout << "\"No\" button clicked. Sides are not swapped. Closing message window.\n";
                                                                // do not swap sides
                                                                messageWindow.close();
                                                            }
                                                        }

                                                    }

                                                    messageWindow.clear();
                                                    messageWindow.draw(text);
                                                    messageWindow.draw(yesButton);
                                                    messageWindow.draw(yesButtonText);
                                                    messageWindow.draw(noButton);
                                                    messageWindow.draw(noButtonText);
                                                    messageWindow.display();
                                                }

                                            }
                                        }
                                        else
                                        {
                                            std::cout << "Pillar limit reached!" << std::endl;
                                            sf::RenderWindow messageWindow(sf::VideoMode(300, 200), "Limit reached");
                                            sf::Text message;
                                            sf::Font font;
                                            sf::RectangleShape closeButton(sf::Vector2f(200, 100));
                                            closeButton.setFillColor(sf::Color::Red);
                                            closeButton.setPosition(150, 100); // Position the button within the messageWindow
                                            sf::Text closeButtonText("Close", font, 24);
                                            closeButtonText.setFillColor(sf::Color::Blue);
                                            closeButtonText.setPosition(closeButton.getPosition() + sf::Vector2f(10, 10)); // Position the text on the button

                                            font.loadFromFile("ARIAL.TTF");
                                            message.setFont(font);
                                            message.setString("Limit of pillars reached");
                                            message.setCharacterSize(24);
                                            message.setFillColor(sf::Color::Red);

                                            sf::FloatRect messageRect = message.getLocalBounds();
                                            message.setOrigin(messageRect.left + messageRect.width / 2.0f, messageRect.top + messageRect.height / 2.0f);
                                            message.setPosition(messageWindow.getView().getCenter());

                                            while (messageWindow.isOpen()) {
                                                sf::Event event;
                                                while (messageWindow.pollEvent(event)) {
                                                    if (event.type == sf::Event::Closed)
                                                        messageWindow.close();
                                                    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                                                        sf::Vector2i mousePos = sf::Mouse::getPosition(messageWindow);
                                                        if (closeButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                                                            std::cout << "Close button clicked. Closing message window." << std::endl;
                                                            closeMessageWindowClicked = true;
                                                            messageWindow.close(); // Close the message window
                                                        }
                                                    }
                                                } if (closeMessageWindowClicked) {
                                                    boardWindow.close(); // Închide fereastra de joc
                                                    boardWindowOpen = false; // Setează starea ferestrei de joc pe închis
                                                    window.create(sf::VideoMode(1920, 1080), "Twixt Game Menu"); // Recreează fereastra de meniu
                                                    closeMessageWindowClicked = false; // Reset the flag
                                                }
                                                messageWindow.clear();
                                                messageWindow.draw(message);
                                                messageWindow.draw(closeButton);
                                                messageWindow.draw(closeButtonText);
                                                messageWindow.display();
                                            }
                                         
                                            std::cout << "Pillar Limit: " << board.m_pillarNumberDef << std::endl;
                                            std::cout << "Board Size: " << board.GetSize() << std::endl;
                                            std::cout << "Red Pillars: " << redPillars.size() << std::endl;
                                            std::cout << "Black Pillars: " << blackPillars.size() << std::endl;

                                            boardWindow.close();
                                            break;

                                        }
                                        break;
                                    }


                              


                            }

                        }

                    }
                }


                //boardWindow.clear(sf::Color::White);
                board.Draw(boardWindow);
                for (auto& pillar : redPillars)
                    pillar.Draw(boardWindow);
                for (const auto& bridge : redBridges)
                    bridge.draw(boardWindow);
                for (auto& pillar : blackPillars)
                    pillar.Draw(boardWindow);
                for (const auto& bridge : blackBridges)
                    bridge.draw(boardWindow);
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
                            board.SetMaxBridgeNumber(board.m_bridgesNumber1);
                            std::cout << "25 bridges button clicked!" << std::endl; // Debug message
                            selectedButtonShadowBridges = &board.button25bridges;
                        }
                        // Check if the 50 bridges button was pressed
                        else if (board.button50bridges.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
                        {
                            board.SetMaxBridgeNumber(board.m_bridgesNumber2);
                            std::cout << "50 bridges button clicked!" << std::endl; // Debug message
                            selectedButtonShadowBridges = &board.button50bridges;
                        }
                        // Check if the 75 bridges button was pressed
                        else if (board.button75bridges.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
                        {
                           board.SetMaxBridgeNumber(board.m_bridgesNumber3);
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

