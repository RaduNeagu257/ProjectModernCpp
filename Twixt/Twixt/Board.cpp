#include "Board.h"
#include <iostream>
Board::Board()
	:m_size(24),
	m_tileSize(30),
	m_boardSize1(18),
	m_boardSize2(24),
	m_boardSize3(30),
	m_pillarNumberDef(50),
	m_pillarNumber1(28),
	m_pillarNumber2(50),
	m_pillarNumber3(78),
	m_bridgesNumberDef(50),
	m_bridgesNumber1(2),
	m_bridgesNumber2(50),
	m_bridgesNumber3(75),
	button18x18({ 100, 50 }),
	button24x24({ 100, 50 }),
	button30x30({ 100, 50 }),
	button28pillars({ 100, 50 }),
	button50pillars({ 100, 50 }),
	button78pillars({ 100, 50 }),
	button25bridges({ 120,50 }),
	button50bridges({ 120,50 }),
	button75bridges({ 120, 50 })


{
	button18x18.setFillColor(sf::Color::White);
	button18x18.setPosition(50, 80); 

	button24x24.setFillColor(sf::Color::White);
	button24x24.setPosition(50, 140); 

	button30x30.setFillColor(sf::Color::White);
	button30x30.setPosition(50, 200);

	button28pillars.setFillColor(sf::Color::White);
	button28pillars.setPosition(450, 80);

	button50pillars.setFillColor(sf::Color::White);
	button50pillars.setPosition(450, 140);

	button78pillars.setFillColor(sf::Color::White);
	button78pillars.setPosition(450, 200);

	button25bridges.setFillColor(sf::Color::White);
	button25bridges.setPosition(800, 80);

	button50bridges.setFillColor(sf::Color::White);
	button50bridges.setPosition(800, 140);

	button75bridges.setFillColor(sf::Color::White);
	button75bridges.setPosition(800, 200);


	// Create the red horizontal lines
	float lineWidth = (m_tileSize + 1) * m_size;
	m_horizontalLine1.setSize({ lineWidth, LINE_THICKNESS });
	m_horizontalLine1.setFillColor(sf::Color::Red);
	//m_horizontalLine1.setPosition(0, m_tileSize);

	m_horizontalLine2.setSize({ lineWidth, LINE_THICKNESS });
	m_horizontalLine2.setFillColor(sf::Color::Red);
	//m_horizontalLine2.setPosition(0, (m_size - 1) * m_tileSize - 2);

	// Create the black vertical lines
	float lineHeight = (m_tileSize + 1) * m_size;
	m_verticalLine1.setSize({ LINE_THICKNESS, lineHeight });
	m_verticalLine1.setFillColor(sf::Color::Black);
	//m_verticalLine1.setPosition(m_tileSize, 0);

	m_verticalLine2.setSize({ LINE_THICKNESS, lineHeight });
	m_verticalLine2.setFillColor(sf::Color::Black);
	//m_verticalLine2.setPosition((m_size - 1) * m_tileSize - 2, 0);
}

void Board::Draw(sf::RenderWindow& BoardWindow)
{
	//Pillar blackPillar(100.0f, 100.0f, sf::Color::Black);
	//Pillar redPillar(150.0f, 150.0f, sf::Color::Red);
	// Calculate the dimensions of the array
	float totalBoardWidth = m_size * m_tileSize;
	float totalBoardHeight = m_size * m_tileSize;


	// Calculate the distance between the corner of the window and the window to be centered
	float offsetX = (BoardWindow.getSize().x - totalBoardWidth) / 2;
	float offsetY = (BoardWindow.getSize().y - totalBoardHeight) / 2;

	// Create the background rectangle
	sf::RectangleShape backgroundRectangle(sf::Vector2f(totalBoardWidth + m_size, totalBoardHeight + m_size));

	// Set its position to the top-left corner of the array
	backgroundRectangle.setPosition(offsetX - m_tileSize * 0.8, offsetY - m_tileSize * 0.8);

	// Set its color to rgb(247, 255, 208) - pale yellow from pictures of the board game
	backgroundRectangle.setFillColor(sf::Color(247, 255, 208));

	// Draw the background rectangle
	BoardWindow.draw(backgroundRectangle); // draw the colored rectangle

	// Centering the array using the previously calculated offsets

	for (U8 i = 0; i < m_size; ++i)
	{
		for (U8 j = 0; j < m_size; ++j)
		{
			// Create the 2D array for the board
			sf::CircleShape tile(DOT_RADIUS);
			tile.setPosition(i * m_tileSize + offsetX, j * m_tileSize + offsetY);
			tile.setOutlineColor(sf::Color::Black);
			tile.setOutlineThickness(1);
			m_tiles.push_back(std::make_tuple(tile, j, i));
			BoardWindow.draw(tile);
		}
	}

	// Declare the mousePosition and mousePostionFloat variables.
	sf::Vector2i mousePosition;
	sf::Vector2f mousePositionFloat;

	// Get the position of the mouse.
	mousePosition = sf::Mouse::getPosition(BoardWindow);

	// Check if the mouse is hovering over a cell.

	for (auto& tile : m_tiles)
	{

		if (std::get<0>(tile).getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
		{
			// Temporarily change the color of the hovered pillar to a light grey
			std::get<0>(tile).setFillColor(sf::Color(200, 200, 200, 255));
			BoardWindow.draw(std::get<0>(tile));
		}
	}

	m_horizontalLine1.setPosition(offsetX - m_tileSize * 0.8, offsetY + DOT_RADIUS * 2.25);
	m_horizontalLine2.setPosition(offsetX - m_tileSize * 0.8, offsetY + (m_size - 1) * m_tileSize - DOT_RADIUS * 0.6);

	m_verticalLine1.setPosition(offsetX + DOT_RADIUS * 2.25, offsetY - m_tileSize * 0.8);
	m_verticalLine2.setPosition(offsetX + (m_size - 1) * m_tileSize - DOT_RADIUS * 0.6, offsetY - m_tileSize * 0.8);

	BoardWindow.draw(m_horizontalLine1);
	BoardWindow.draw(m_horizontalLine2);
	BoardWindow.draw(m_verticalLine1);
	BoardWindow.draw(m_verticalLine2);
	//blackPillar.draw(BoardWindow);
	//redPillar.draw(BoardWindow);
	BoardWindow.draw(button18x18);
	BoardWindow.draw(button24x24);
	BoardWindow.draw(button30x30);
	}
void Board::SetBoardSize(U8 size)
{
	m_size = size;
	m_tiles.clear(); // clean the tiles vector to add new tiles
	

	for (U8 i = 0; i < m_size; ++i)
	{
		for (U8 j = 0; j < m_size; ++j)
		{
			sf::CircleShape tile(DOT_RADIUS);
			tile.setPosition(i * m_tileSize, j * m_tileSize);
			tile.setOutlineColor(sf::Color::Black);
			tile.setOutlineThickness(1);
			m_tiles.push_back(std::make_tuple(tile, j, i));
		}
	}

	// Redraw the horizontal lines
	float lineWidth = (m_tileSize + 1) * m_size;
	m_horizontalLine1.setSize({ lineWidth, LINE_THICKNESS });
	m_horizontalLine1.setFillColor(sf::Color::Red);
	m_horizontalLine1.setPosition(0, m_tileSize);

	m_horizontalLine2.setSize({ lineWidth, LINE_THICKNESS });
	m_horizontalLine2.setFillColor(sf::Color::Red);
	m_horizontalLine2.setPosition(0, (m_size - 1) * m_tileSize - 2);

	// Redraw the vertical lines
	float lineHeight = (m_tileSize + 1) * m_size;
	m_verticalLine1.setSize({ LINE_THICKNESS, lineHeight });
	m_verticalLine1.setFillColor(sf::Color::Black);
	m_verticalLine1.setPosition(m_tileSize, 0);

	m_verticalLine2.setSize({ LINE_THICKNESS, lineHeight });
	m_verticalLine2.setFillColor(sf::Color::Black);
	m_verticalLine2.setPosition((m_size - 1) * m_tileSize - 2, 0);
}

void Board::PlaceBridge(Pillar& selectedPillar, const std::vector<Pillar>& existingPillars, std::vector<Bridge>& existingBridges,sf::Color player)
{
	if (MaxNumberBridgesReached(existingBridges))
	{
		// Afiseaza fereastra atunci cand se atinge limita de poduri
		sf::RenderWindow limitWindow(sf::VideoMode(500, 300), "Limita de Poduri Atinsa", sf::Style::Close);

		sf::Font font;
		font.loadFromFile("arial.ttf");
		sf::Text text("Limita de poduri a fost atinsa!", font, 16);
		text.setPosition(10, 20);

		sf::RectangleShape closeButton(sf::Vector2f(80, 30));
		closeButton.setPosition(110, 60);
		closeButton.setFillColor(sf::Color::Red);

		sf::Text closeButtonText("Close", font, 16);
		closeButtonText.setPosition(130, 65);
		closeButtonText.setFillColor(sf::Color::White);

		limitWindow.clear(sf::Color::White);
		limitWindow.draw(text);
		limitWindow.draw(closeButton);
		limitWindow.draw(closeButtonText);
		limitWindow.display();

		sf::Event event;
		while (limitWindow.isOpen())
		{
			while (limitWindow.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					limitWindow.close();
				else if (event.type == sf::Event::MouseButtonPressed)
				{
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						sf::Vector2f mousePosition = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
						if (closeButton.getGlobalBounds().contains(mousePosition))
						{
							limitWindow.close();
							// Închide jocul
							exit(0);
						}
					}
				}
			}
		}

		return;
	}
	bool found = false;
	for (auto& pillar : existingPillars) // check every pillar other than the previously selected one if a bridge can be placed
		if (selectedPillar.GetPosition() != pillar.GetPosition()) // avoid checking the same pillar
		{
			U8 dx = std::abs(pillar.m_col - selectedPillar.m_col);
			U8 dy = std::abs(pillar.m_row - selectedPillar.m_row);
			std::cout << unsigned(dx) << " " << unsigned(dy) << "\n";
			if (((dx == 2 && dy == 1) || (dx == 1 && dy == 2))) // check if pillars are in an L shape
			{
				if (existingBridges.empty()) // check if there are no bridges for optimization purposes
				{
					std::cout << "No existing Bridges\n";

					//// Create a pop-up window indicating that there are no pillars to place a bridge between
					//sf::RenderWindow noBridgeWindow(sf::VideoMode(300, 100), "No Pillars for Bridge", sf::Style::Close);

					//// Create a text message
					//sf::Font font;
					//font.loadFromFile("arial.ttf");
					//sf::Text text("No pillars found to place a bridge.", font, 16);
					//text.setPosition(10, 20);

					//// Draw the text
					//noBridgeWindow.clear(sf::Color::White);
					//noBridgeWindow.draw(text);
					//noBridgeWindow.display();

					//sf::Event event;
					//while (noBridgeWindow.isOpen())
					//{
					//	while (noBridgeWindow.pollEvent(event))
					//	{
					//		if (event.type == sf::Event::Closed)
					//			noBridgeWindow.close();
					//	}
					//}
					found = true;
					existingBridges.emplace_back(selectedPillar, pillar, player);
					if (MaxNumberBridgesReached(existingBridges)) // check if number of maximum allowed bridges has been reached
					{
						return;
					}
				}
				else
				for (auto& bridge : existingBridges) // check all existing bridges in order to make sure that a bridge doesn't already exist between 2 pillars
					if (!((bridge.m_startPillar.GetPosition() == selectedPillar.GetPosition() && bridge.m_stopPillar.GetPosition() == pillar.GetPosition()) ||
						(bridge.m_startPillar.GetPosition() == pillar.GetPosition() && bridge.m_stopPillar.GetPosition() == selectedPillar.GetPosition())))
					{
						found = true;
						existingBridges.emplace_back(selectedPillar, pillar, player);
						if (MaxNumberBridgesReached(existingBridges))// check if number of maximum allowed bridges has been reached
						{
							
							return; //expand outcome later
						}
					}
			}
		}
	if (found)
		std::cout << "Placed bridge\n";
	else
		std::cout << "Did not find any pillar to place a bridge between\n";
	//if (!found)
	//{
	//	sf::RenderWindow messageWindow2(sf::VideoMode(500, 300), "limit of bridges reached");
	//	sf::Text message;
	//	sf::Font font;
	//	font.loadFromFile("ARIAL.TFF");
	//	message.setFont(font);
	//	message.setString("Limit of pillars reached");
	//	message.setCharacterSize(24);
	//	message.setFillColor(sf::Color::Red);
	//	sf::FloatRect messageRect = message.getLocalBounds();
	//	 message.setOrigin(messageRect.left + messageRect.width / 2.0f, messageRect.top + messageRect.height / 2.0f);
	//	 message.setPosition(messageWindow2.getView().getCenter());
	//	 messageWindow2.clear();
	//	 messageWindow2.draw(message);
 //                                  
	//}
}

std::vector<std::tuple<sf::CircleShape, U8, U8>> Board::getTiles() const
{
	return m_tiles;
}

U8 Board::getTileSize() const
{
	return m_tileSize;
}

U8 Board::GetSize() const
{
	return m_size;
}

void Board::DrawSettingsButtons(sf::RenderWindow& settingsWindow)
{
	//text for board buttons
	sf::Text text18x18;
	sf::Font settingsfont;

	settingsfont.loadFromFile("ARIAL.TTF");
	text18x18.setFont(settingsfont); // Set the font to our text
	text18x18.setString("18x18"); // Set the button label text
	text18x18.setCharacterSize(24); // Set the text size
	text18x18.setFillColor(sf::Color::Black); // Set the text color

	sf::FloatRect textRectBoard = text18x18.getLocalBounds();

	// Position the text relative to the button
	text18x18.setOrigin(textRectBoard.left + textRectBoard.width / 2.0f, textRectBoard.top + textRectBoard.height / 2.0f);
	text18x18.setPosition(sf::Vector2f(button18x18.getPosition().x + button18x18.getSize().x / 2.0f, button18x18.getPosition().y + button18x18.getSize().y / 2.0f));

	sf::Text text24x24 = text18x18;

	text24x24.setString("24x24");
	// Position the text relative to the button
	text24x24.setPosition(sf::Vector2f(button24x24.getPosition().x + button24x24.getSize().x / 2.0f, button24x24.getPosition().y + button24x24.getSize().y / 2.0f));

	sf::Text text30x30 = text18x18;

	text30x30.setString("30x30");
	// Position the text relative to the button
	text30x30.setPosition(sf::Vector2f(button30x30.getPosition().x + button30x30.getSize().x / 2.0f, button30x30.getPosition().y + button30x30.getSize().y / 2.0f));

	//text for pillar buttons
	sf::Text text28Pillars;

	settingsfont.loadFromFile("ARIAL.TTF");
	text28Pillars.setFont(settingsfont); // Set the font to our text
	text28Pillars.setString("28 pillars"); // Set the button label text
	text28Pillars.setCharacterSize(24); // Set the text size
	text28Pillars.setFillColor(sf::Color::Black); // Set the text color

	sf::FloatRect textRectPillars = text28Pillars.getLocalBounds();

	// Position the text relative to the button
	text28Pillars.setOrigin(textRectPillars.left + textRectPillars.width / 2.0f, textRectPillars.top + textRectPillars.height / 2.0f);
	text28Pillars.setPosition(sf::Vector2f(button28pillars.getPosition().x + button28pillars.getSize().x / 2.0f, button28pillars.getPosition().y + button28pillars.getSize().y / 2.0f));

	sf::Text text50Pillars = text28Pillars;

	text50Pillars.setString("50 pillars");
	// Position the text relative to the button
	text50Pillars.setPosition(sf::Vector2f(button50pillars.getPosition().x + button50pillars.getSize().x / 2.0f, button50pillars.getPosition().y + button50pillars.getSize().y / 2.0f));

	sf::Text text78Pillars = text28Pillars;

	text78Pillars.setString("78 pillars");
	// Position the text relative to the button
	text78Pillars.setPosition(sf::Vector2f(button78pillars.getPosition().x + button78pillars.getSize().x / 2.0f, button78pillars.getPosition().y + button78pillars.getSize().y / 2.0f));

	//text for bridges button
	sf::Text text25bridges;

	settingsfont.loadFromFile("ARIAL.TTF");
	text25bridges.setFont(settingsfont); // Set the font to our text
	text25bridges.setString("25 bridges"); // Set the button label text
	text25bridges.setCharacterSize(24); // Set the text size
	text25bridges.setFillColor(sf::Color::Black); // Set the text color

	sf::FloatRect textRectBridges = text25bridges.getLocalBounds();

	// Position the text relative to the button
	text25bridges.setOrigin(textRectBridges.left + textRectBridges.width / 2.0f, textRectBridges.top + textRectBridges.height / 2.0f);
	text25bridges.setPosition(sf::Vector2f(button25bridges.getPosition().x + button25bridges.getSize().x / 2.0f, button25bridges.getPosition().y + button25bridges.getSize().y / 2.0f));

	sf::Text text50bridges = text25bridges;

	text50bridges.setString("50 bridges");
	// Position the text relative to the button
	text50bridges.setPosition(sf::Vector2f(button50bridges.getPosition().x + button50bridges.getSize().x / 2.0f, button50bridges.getPosition().y + button50bridges.getSize().y / 2.0f));

	sf::Text text75bridges = text25bridges;

	text75bridges.setString("75 bridges");
	// Position the text relative to the button
	text75bridges.setPosition(sf::Vector2f(button75bridges.getPosition().x + button75bridges.getSize().x / 2.0f, button75bridges.getPosition().y + button75bridges.getSize().y / 2.0f));

	settingsWindow.draw(button18x18);
	settingsWindow.draw(text18x18);

	settingsWindow.draw(button24x24);
	settingsWindow.draw(text24x24);

	settingsWindow.draw(button30x30);
	settingsWindow.draw(text30x30);

	settingsWindow.draw(button28pillars);
	settingsWindow.draw(text28Pillars);

	settingsWindow.draw(button50pillars);
	settingsWindow.draw(text50Pillars);

	settingsWindow.draw(button78pillars);
	settingsWindow.draw(text78Pillars);

	settingsWindow.draw(button25bridges);
	settingsWindow.draw(text25bridges);

	settingsWindow.draw(button50bridges);
	settingsWindow.draw(text50bridges);

	settingsWindow.draw(button75bridges);
	settingsWindow.draw(text75bridges);


}

void Board::SwapLines()
{
	m_horizontalLine1.setFillColor(sf::Color::Black);
	m_horizontalLine2.setFillColor(sf::Color::Black);
	m_verticalLine1.setFillColor(sf::Color::Red);
	m_verticalLine2.setFillColor(sf::Color::Red);
}

bool Board::IsPillarThere(const std::vector<Pillar>& pillars, const Pillar& tempPillar)
{
	//each existing pillar is checked in case the new pillar would be placed on a position which already has a pillar on it
	for (const auto& pillar : pillars) {
		if (pillar.GetPosition() == tempPillar.GetPosition())
			return true;
	}
	return false;
}

void Board::PlacePillar(std::vector<Pillar>& pillars, Pillar& tempPillar, sf::Color& player, U16& pillarAdded)
{
	if(!MaxNumberPillarsReached(pillars))
	{
		if (!IsPillarThere(pillars, tempPillar))
		{

			std::cout << "Pillar button clicked!" << std::endl; // debug message
			pillarAdded++;
			pillars.emplace_back(tempPillar); //pillar is added to the vector of existing pillars

		}
	}
	else
		std::cout << "There is already a pillar there!" << std::endl;

}
void Board::SwapSides(std::vector<Pillar>& redPillars, std::vector<Pillar>& blackPillars)
{
	// swap the pillars
	std::swap(redPillars, blackPillars);
	// swap the color of the pillars
	for (auto& pillar : redPillars)
		pillar.SetColor(sf::Color::Red);
	for (auto& pillar : blackPillars)
		pillar.SetColor(sf::Color::Black);
}

bool Board::PlacePillarInBase(Pillar& pillar)
{
	// check if a pillar is to be placed in one of the inaccessible four corners of the board
	if ((pillar.m_col == 0 && (pillar.m_row == 0) || pillar.m_col == m_size - 1))
		return false;
	if ((pillar.m_col == m_size - 1 && (pillar.m_row == 0) || pillar.m_col == m_size - 1))
		return false;

	// check if pillar is to be placed in a base
	if (pillar.m_col == 0 || pillar.m_col == m_size - 1) 
		return (pillar.GetColor() == m_verticalLine1.getFillColor() || pillar.GetColor() == m_verticalLine2.getFillColor());
	if (pillar.m_row == 0 || pillar.m_row == m_size - 1)
		return (pillar.GetColor() == m_horizontalLine1.getFillColor() || pillar.GetColor() == m_horizontalLine2.getFillColor());

	return true;
}

U8 Board::GetMaxPillarNumber() const 
{
	return m_pillarNumberDef;
}

U8 Board::GetMaxBridgeNumber() const
{
	return m_bridgesNumberDef;
}

void Board::SetMaxBridgeNumber(U8 bridgeNumber) 
{
	m_bridgesNumberDef = bridgeNumber;
}

bool Board::MaxNumberPillarsReached(std::vector<Pillar>& pillars)
{
	return pillars.size() >= m_pillarNumberDef;
}

bool Board::MaxNumberBridgesReached(std::vector<Bridge>& bridges)
{
	return bridges.size() >= m_bridgesNumberDef;
}

bool Board::WinningChainCreated(std::vector<Bridge>& bridges)
{
	U8 minimumBridgesNumber = m_size / 2 + m_size % 2;
	if (bridges.size() < minimumBridgesNumber) // check if the number of placed bridges is lower than the minimum required to create a chain from one border to the next
		return false;
}

void Board::SetPillarNumber(U8 pillarNumber)
{
	m_pillarNumberDef = pillarNumber;
}

