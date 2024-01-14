#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include<iostream>
#include "Board.h"
#include "Pillar.h"
#include "Bridge.h"
float BRIDGE_LINE_THICKNESS = 5.0f;

void DrawErrorWindow(const std::string& errorText);
void DrawSwapWindow(bool& answer);

enum Messages{
    PillarLimit,
    BridgesLimit,
    RedPlayerWon,
    BlackPlayerWon,
    WrongBase,
    PillarColision
};

const std::map<Messages, std::tuple<std::string, std::string, bool>> message = {
    {PillarLimit, {"Limit reached", "Limit of pillars reached", true}},
    {BridgesLimit, {"Limit reached", "Limit of bridges reached", true}},
    {RedPlayerWon, {"Red player has won", "The Red player has won", true}},
    {BlackPlayerWon, {"Black player has won", "The Black player has won", true}},
    {WrongBase, {"Wrong base", "Pillar placed in the wrong base", false}},
    {PillarColision, {"Pillar Collision", "There already is a pillar in this position", false}},
};

void showMessage(Messages errorMessage, sf::RenderWindow& gameWindow) {
    std::string windowTitle, windowMessage;
    bool windowClosure;
    std::tie(windowTitle, windowMessage, windowClosure) =  message.at(errorMessage);
    sf::RenderWindow messageWindow(sf::VideoMode(500, 300), "Message");
    sf::Text messageText;
    sf::Font font;
    sf::RectangleShape closeButton(sf::Vector2f(70, 30));
    closeButton.setFillColor(sf::Color::Red);
    closeButton.setPosition(350, 240);

    sf::Text closeButtonText("Close", font, 18);
    closeButtonText.setFillColor(sf::Color::Blue);
    closeButtonText.setPosition(closeButton.getPosition() + sf::Vector2f(10, 10));

    if (!font.loadFromFile("ARIAL.TTF")) {
        // Failure to load font
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    messageText.setFont(font);
   
    messageText.setString(windowMessage);
    messageWindow.setTitle(windowTitle);

    messageText.setCharacterSize(24);
    messageText.setFillColor(sf::Color::Red);

    sf::FloatRect messageRect = messageText.getLocalBounds();
    messageText.setOrigin(messageRect.left + messageRect.width / 2.0f, messageRect.top + messageRect.height / 2.0f);
    messageText.setPosition(messageWindow.getView().getCenter());

    while (messageWindow.isOpen()) {
        sf::Event event;
        while (messageWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                messageWindow.close();
                if (windowClosure) {
                    gameWindow.close();
                }
            }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(messageWindow);
                if (closeButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    messageWindow.close();
                    if (windowClosure) {
                        gameWindow.close();
                    }
                }
            }
        }

        messageWindow.clear();
        messageWindow.draw(messageText);
        messageWindow.draw(closeButton);
        messageWindow.draw(closeButtonText);
        messageWindow.display();
    }
}
    void centerTextInButton(sf::Text& buttonText, sf::RectangleShape& button) {
        buttonText.setPosition(
            button.getPosition().x + (button.getSize().x - buttonText.getGlobalBounds().width) / 2,
            button.getPosition().y + (button.getSize().y - buttonText.getGlobalBounds().height) / 2
        );
    }

int main() {
   
    Board board;
    // Open the window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Twixt Game");
    window.setFramerateLimit(60);
    bool isSelecting = false;
    sf::Vector2f startPosition;
    sf::Vector2f endPosition;
    Pillar startPillar;
    Pillar stopPillar;

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("../Images/banner.jpg")) 
    {
        //Error loading image
        std::cerr << "Failed to load background image!" << std::endl;
        return -1;
    }
    sf::Sprite backgroundImage(backgroundTexture);
    backgroundImage.setScale(static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x, 
                             static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y);

    // Declare the "Start" button
    sf::RectangleShape startButton(sf::Vector2f(250, 70));
    startButton.setFillColor(sf::Color::Black);
    startButton.setPosition(860, 520);
    startButton.setOutlineThickness(0);  

    // Declare the "Settings" button
    sf::RectangleShape settingsButton(sf::Vector2f(250, 70));
    settingsButton.setFillColor(sf::Color::Black);
    settingsButton.setPosition(860, 630);
    settingsButton.setOutlineThickness(0);

    // Declare the "Instructions" button
    sf::RectangleShape instructionButton(sf::Vector2f(250, 70));
    instructionButton.setFillColor(sf::Color::Black);
    instructionButton.setPosition(860, 730);
    instructionButton.setOutlineThickness(0);

    // Declare the "Ok" button
    sf::RectangleShape okButton(sf::Vector2f(250, 70));
    okButton.setFillColor(sf::Color::Black);
    okButton.setPosition(50, 300);
    okButton.setOutlineThickness(0);

    // Declare the text for the "ok" button
    sf::Font buttonFont;
    buttonFont.loadFromFile("ARIAL.TTF");
    sf::Text okButtonText("OK", buttonFont, 40);
    okButtonText.setFillColor(sf::Color(255, 215, 0));
    okButtonText.setStyle(sf::Text::Bold);
    centerTextInButton(okButtonText, okButton);

    // Declare the text for the "Start" button
    sf::Font font;
    font.loadFromFile("ARIAL.TTF");
    sf::Font fontButtons;
    fontButtons.loadFromFile("WEST____.TTF");
    sf::Text startButtonText("Play!", fontButtons, 40);
    startButtonText.setFillColor(sf::Color(255, 215, 0));
    startButtonText.setStyle(sf::Text::Bold);
    centerTextInButton(startButtonText, startButton);

    // Declare the text for the "Instructions" button
    sf::Text instructionsButtonText("Instructions", fontButtons, 40);
    instructionsButtonText.setFillColor(sf::Color(255, 215, 0));
    instructionsButtonText.setStyle(sf::Text::Bold);
    centerTextInButton(instructionsButtonText, instructionButton);

    // Declare the text for the "Settings" button
    sf::Text settingsButtonText("Settings", fontButtons, 40);
    settingsButtonText.setFillColor(sf::Color(255, 215, 0));
    settingsButtonText.setStyle(sf::Text::Bold);
    centerTextInButton(settingsButtonText, settingsButton);

    bool instructionsWindowOpen = false;
    bool boardWindowOpen = false;
    bool settingsWindowOpen = false;

    sf::RenderWindow instructionsWindow;
    sf::RenderWindow settingsWindow;
    sf::RenderWindow boardWindow;
    bool closeMessageWindowClicked = false;


    // Main game loop
    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) 
                window.close();

            // Check if the left mouse click is pressed
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) 
            {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                sf::Vector2f mousePositionFloat(mousePosition.x, mousePosition.y);

                // Check if the "Instructions" button is clicked
                if (instructionButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) 
                {
                    instructionsWindowOpen = true;
                    std::cout << "Instructions button clicked!" << std::endl; // Debug message
                }
                // Check if the "Board game" button is clicked
                else if (startButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) 
                {
                    boardWindowOpen = true;
                    std::cout << "Board Game button clicked!" << std::endl; //Debug message
                }
                //Check if the "Settings" button is clicked
                else  if (settingsButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) 
                {
                    settingsWindowOpen = true;
                    std::cout << "Settings button clicked!" << std::endl; // Debug message
                }

            }

        }
        if (instructionsWindowOpen) 
        {
            if (!instructionsWindow.isOpen()) 
            {
                instructionsWindow.create(sf::VideoMode(1100, 500), "Instructions", sf::Style::Close);
                instructionsWindow.setFramerateLimit(60);
            }

            sf::Event instructionsEvent;
            while (instructionsWindow.pollEvent(instructionsEvent)) 
            {
                if (instructionsEvent.type == sf::Event::Closed) 
                {
                    instructionsWindow.close();
                    instructionsWindowOpen = false;
                }
            }
            //instructionsWindow.clear(sf::Color::Cyan);
            sf::Font instructions2Font;

            sf::Texture instructionsImageTexture;
            if (!instructionsImageTexture.loadFromFile("../Images/page.jpg")) 
            {
                std::cerr << "Failed to load background image!" << std::endl;
                return -1;
            }

            sf::Sprite instructionsImage(instructionsImageTexture);
            instructionsImage.setScale(static_cast<float>(instructionsWindow.getSize().x) / instructionsImageTexture.getSize().x,
                                       static_cast<float>(instructionsWindow.getSize().y) / instructionsImageTexture.getSize().y);

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

            instructionsWindow.draw(instructionsImage);
            instructions2Text.setFillColor(sf::Color::Black);
            instructions2Text.setPosition(50, 50);
            instructionsWindow.draw(instructions2Text);

            instructionsWindow.display();
        }

        if (boardWindowOpen) 
        {
            U16 pillarAdded = 0;
            if (!boardWindow.isOpen()) 
            {
                boardWindow.create(sf::VideoMode(1920, 1080), "Game Window", sf::Style::Close);
                boardWindow.setFramerateLimit(60);
            }
            std::vector<Pillar> redPillars, blackPillars;
            std::vector<Bridge> redBridges, blackBridges;
            std::cout << unsigned(board.m_bridgesNumber1)<<" "<<unsigned(board.m_bridgesNumber2)<<" "<<unsigned(board.m_bridgesNumber3)<<" " << unsigned(board.m_bridgesNumberDef) << "\n";
            sf::Color player = sf::Color::Red;
            while (boardWindow.isOpen()) 
            {
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
                                tempPillar.setPosition(std::get<0>(tile).getPosition());
                                  if (player == sf::Color::Red) // Red side's turn
                                  {

                                         
                                      if(!board.MaxNumberPillarsReached(redPillars))
                                        {

                                            if (board.PlacePillarInBase(tempPillar)){
                                                if (!board.IsPillarThere(redPillars, tempPillar) && !board.IsPillarThere(blackPillars, tempPillar))
                                                {
                                                    std::cout << "Red ";
                                                    board.PlacePillar(redPillars, tempPillar, pillarAdded);
                                                    if (!board.PlaceBridge(tempPillar, redPillars, redBridges, player,blackBridges)) {
                                                        showMessage(BridgesLimit, boardWindow);
                                                    }
                                                    std::cout << "winning chain: " << board.WinningChainCreated(redBridges, redPillars, player) << "\n";
                                                    if (board.WinningChainCreated(redBridges, redPillars, player))
                                                    {
                                                        showMessage(RedPlayerWon, boardWindow);
                                                        break;
                                                    }
                                                    player = sf::Color::Black;
                                                    
                                                }
                                                else
                                                {
                                                    showMessage(PillarColision, boardWindow);
                                                }

                                            }
                                            else {
                                                showMessage(WrongBase, boardWindow);
                                            }
                                        }
                                        else
                                        {
                                          showMessage(PillarLimit, boardWindow);
                                          break;

                                        }
                                      
                                        break;
                                    }
                                    else // Black side's turn
                                    {
                                        if (!board.MaxNumberPillarsReached(blackPillars))
                                        {
                                            if (board.PlacePillarInBase(tempPillar)) {
                                                if (!board.IsPillarThere(blackPillars, tempPillar) && !board.IsPillarThere(redPillars, tempPillar))
                                                {
                                                    std::cout << "Black ";
                                                    board.PlacePillar(blackPillars, tempPillar, pillarAdded);
                                                    if (!board.PlaceBridge(tempPillar, blackPillars, blackBridges, player,redBridges)) {
                                                        showMessage(BridgesLimit, boardWindow);
                                                    }
                                                    std::cout << "winning chain: " << board.WinningChainCreated(blackBridges, blackPillars, player) << "\n";
                                                    if (board.WinningChainCreated(blackBridges, blackPillars, player))
                                                    {
                                                        showMessage(BlackPlayerWon, boardWindow);
                                                        break;
                                                    }
                                                    player = sf::Color::Red;
                                                    
                                                }
                                                else
                                                {
                                                    showMessage(PillarColision, boardWindow);
                                                }
                                            }
                                            else {
                                                showMessage(WrongBase, boardWindow);
                                            }
                                            
                                            if (blackPillars.size() == redPillars.size() && pillarAdded == 2) //Allow the black side to choose to swap sides after the first turn
                                            {   
                                                bool answer;
                                                DrawSwapWindow(answer);
                                                if (answer == true)
                                                {
                                                    std::cout << "\"Yes\" button clicked. Sides are swapped. Closing message window." << std::endl;
                                                    // Swap the pillars and the drawn vertical/horizontal lines
                                                    Board::SwapSides(redPillars, blackPillars);
                                                    board.SwapLines();
                                                }
                                                else
                                                {
                                                    //do nothing
                                                    std::cout << "\"No\" button clicked. Sides are not swapped. Closing message window.\n";
                                                }
                                            }
                                        }
                                        else
                                        {
                                            showMessage(PillarLimit, boardWindow);
                                            std::cout << "Pillar Limit: " << board.m_pillarNumberDef << std::endl;
                                            std::cout << "Board Size: " << board.GetSize() << std::endl;
                                            std::cout << "Red Pillars: " << redPillars.size() << std::endl;
                                            std::cout << "Black Pillars: " << blackPillars.size() << std::endl;

                                            //boardWindow.close();
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
                sf::Texture settingsImageTexture;
                if (!settingsImageTexture.loadFromFile("../Images/page.jpg"))
                {
                    std::cerr << "Failed to load background image!" << std::endl;
                    return -1;
                }

                sf::Sprite settingsImage(settingsImageTexture);
                settingsImage.setScale(static_cast<float>(settingsWindow.getSize().x) / settingsImageTexture.getSize().x,
                    static_cast<float>(settingsWindow.getSize().y) / settingsImageTexture.getSize().y);
                settingsWindow.setFramerateLimit(60);

            }
            sf::Texture settingsImageTexture;
            if (!settingsImageTexture.loadFromFile("../Images/page.jpg"))
            {
                std::cerr << "Failed to load background image!" << std::endl;
                return -1;
            }

            sf::Sprite settingsImage(settingsImageTexture);
            settingsImage.setScale(static_cast<float>(settingsWindow.getSize().x) / settingsImageTexture.getSize().x,
                static_cast<float>(settingsWindow.getSize().y) / settingsImageTexture.getSize().y);
           

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
                settingsWindow.clear();
                settingsWindow.draw(settingsImage);

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
        //window.clear(sf::Color::White);

        // Add button
        window.draw(backgroundImage);
       // window.draw(titleText);
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

void DrawErrorWindow(const std::string& errorText)
{
    sf::RenderWindow errorWindow(sf::VideoMode(500, 200), "Error");
    sf::Text errorMessage;
    sf::Font font;

    if (!font.loadFromFile("ARIAL.TTF")) {
        std::cerr << "Error: Font not foumd!! " << std::endl;
        return;
    
    }
    errorMessage.setFont(font);
    errorMessage.setString(errorText);
    errorMessage.setCharacterSize(24);
    errorMessage.setFillColor(sf::Color::Red);

    //Making sure its in the center
    sf::FloatRect textRect = errorMessage.getLocalBounds();
    errorMessage.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    errorMessage.setPosition(errorWindow.getView().getCenter());

    while (errorWindow.isOpen()) {
        sf::Event event;
        while (errorWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                errorWindow.close();
        }

        errorWindow.clear();
        errorWindow.draw(errorMessage);
        errorWindow.display();
    }
}

void DrawSwapWindow(bool& answer)
{
    sf::RenderWindow swapWindow(sf::VideoMode(500, 200), "Swap sides");

    sf::Text text;
    sf::Font font;

    if (!font.loadFromFile("ARIAL.TTF")) {
        std::cerr << "Error: Font not found!" << std::endl;
        return;
    }
    text.setFont(font);
    text.setString("Do you want to swap sides?");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);
    
    //Making sure its in the center
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(swapWindow.getView().getCenter());

    //yes or no buttons
    sf::RectangleShape yesButton(sf::Vector2f(75, 50));
    sf::RectangleShape noButton(sf::Vector2f(75, 50));
    yesButton.setFillColor(sf::Color::Red);
    noButton.setFillColor(sf::Color::Red);
    yesButton.setPosition(175, 150);
    noButton.setPosition(250, 150);

    sf::Text yesButtonText("Yes", font, 24);
    sf::Text noButtonText("No", font, 24);
    yesButtonText.setFillColor(sf::Color::Blue);
    noButtonText.setFillColor(sf::Color::Blue);
    yesButtonText.setOrigin(yesButtonText.getLocalBounds().width / 2, yesButtonText.getLocalBounds().height / 2);
    noButtonText.setOrigin(noButtonText.getLocalBounds().width / 2, noButtonText.getLocalBounds().height / 2);
    yesButtonText.setPosition(yesButton.getPosition().x + yesButton.getSize().x / 2, yesButton.getPosition().y + yesButton.getSize().y / 2);
    noButtonText.setPosition(noButton.getPosition().x + noButton.getSize().x / 2, noButton.getPosition().y + noButton.getSize().y / 2);
    
    while(swapWindow.isOpen()){
        sf::Event event;
        while (swapWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                swapWindow.close();
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(swapWindow);
                if (yesButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    answer = true;
                    swapWindow.close();
                }
                else if (noButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    answer = false;
                    swapWindow.close();
    
                }
            }
        }
        swapWindow.clear();
        swapWindow.draw(text);
        swapWindow.draw(yesButton);
        swapWindow.draw(noButton);
        swapWindow.draw(yesButtonText);
        swapWindow.draw(noButtonText);
        swapWindow.display();
    }



}
