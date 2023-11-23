#include "Board.h"
#include "Pillar.h"
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
	m_bridgesNumber1(25),
	m_bridgesNumber2(50),
	m_bridgesNumber3(75)



{
	button18x18.setSize({ 100, 50 });
	button18x18.setFillColor(sf::Color::White);
	button18x18.setPosition(50, 80); 

	button24x24.setSize({ 100, 50 });
	button24x24.setFillColor(sf::Color::White);
	button24x24.setPosition(50, 140); 

	button30x30.setSize({ 100, 50 });
	button30x30.setFillColor(sf::Color::White);
	button30x30.setPosition(50, 200);

	button28pillars.setSize({ 100, 50 });
	button28pillars.setFillColor(sf::Color::White);
	button28pillars.setPosition(450, 80);

	button50pillars.setSize({ 100, 50 });
	button50pillars.setFillColor(sf::Color::White);
	button50pillars.setPosition(450, 140);

	button78pillars.setSize({ 100, 50 });
	button78pillars.setFillColor(sf::Color::White);
	button78pillars.setPosition(450, 200);

	button25bridges.setSize({ 120,50 });
	button25bridges.setFillColor(sf::Color::White);
	button25bridges.setPosition(800, 80);

	button50bridges.setSize({ 120,50 });
	button50bridges.setFillColor(sf::Color::White);
	button50bridges.setPosition(800, 140);

	button75bridges.setSize({ 120,50 });
	button75bridges.setFillColor(sf::Color::White);
	button75bridges.setPosition(800, 200);


	// Create the red horizontal lines
	float lineWidth = (m_tileSize + 1) * m_size;
	m_redHorizontalLine1.setSize({ lineWidth, LINE_THICKNESS });
	m_redHorizontalLine1.setFillColor(sf::Color::Red);
	//m_redHorizontalLine1.setPosition(0, m_tileSize);

	m_redHorizontalLine2.setSize({ lineWidth, LINE_THICKNESS });
	m_redHorizontalLine2.setFillColor(sf::Color::Red);
	//m_redHorizontalLine2.setPosition(0, (m_size - 1) * m_tileSize - 2);

	// Create the black vertical lines
	float lineHeight = (m_tileSize + 1) * m_size;
	m_blackVerticalLine1.setSize({ LINE_THICKNESS, lineHeight });
	m_blackVerticalLine1.setFillColor(sf::Color::Black);
	//m_blackVerticalLine1.setPosition(m_tileSize, 0);

	m_blackVerticalLine2.setSize({ LINE_THICKNESS, lineHeight });
	m_blackVerticalLine2.setFillColor(sf::Color::Black);
	//m_blackVerticalLine2.setPosition((m_size - 1) * m_tileSize - 2, 0);
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

	for (int i = 0; i < m_size; ++i)
	{
		for (int j = 0; j < m_size; ++j)
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

	m_redHorizontalLine1.setPosition(offsetX - m_tileSize * 0.8, offsetY + DOT_RADIUS * 2.25);
	m_redHorizontalLine2.setPosition(offsetX - m_tileSize * 0.8, offsetY + (m_size - 1) * m_tileSize - DOT_RADIUS * 0.6);

	m_blackVerticalLine1.setPosition(offsetX + DOT_RADIUS * 2.25, offsetY - m_tileSize * 0.8);
	m_blackVerticalLine2.setPosition(offsetX + (m_size - 1) * m_tileSize - DOT_RADIUS * 0.6, offsetY - m_tileSize * 0.8);

	BoardWindow.draw(m_redHorizontalLine1);
	BoardWindow.draw(m_redHorizontalLine2);
	BoardWindow.draw(m_blackVerticalLine1);
	BoardWindow.draw(m_blackVerticalLine2);
	//blackPillar.draw(BoardWindow);
	//redPillar.draw(BoardWindow);
	BoardWindow.draw(button18x18);
	BoardWindow.draw(button24x24);
	BoardWindow.draw(button30x30);
	}
void Board::SetBoardSize(int size)
{
	m_size = size;
	m_tileSize = 30; // Setează dimensiunea inițială a fiecărui pătrat
	m_tiles.clear(); // Curăță vectorul de cercuri pentru a adăuga noi cercuri cu dimensiunile actualizate

	for (int i = 0; i < m_size; ++i)
	{
		for (int j = 0; j < m_size; ++j)
		{
			sf::CircleShape tile(DOT_RADIUS);
			tile.setPosition(i * m_tileSize, j * m_tileSize);
			tile.setOutlineColor(sf::Color::Black);
			tile.setOutlineThickness(1);
			m_tiles.push_back(std::make_tuple(tile, j, i));
		}
	}

	// Regenerează liniile orizontale roșii
	float lineWidth = (m_tileSize + 1) * m_size;
	m_redHorizontalLine1.setSize({ lineWidth, LINE_THICKNESS });
	m_redHorizontalLine1.setFillColor(sf::Color::Red);
	m_redHorizontalLine1.setPosition(0, m_tileSize);

	m_redHorizontalLine2.setSize({ lineWidth, LINE_THICKNESS });
	m_redHorizontalLine2.setFillColor(sf::Color::Red);
	m_redHorizontalLine2.setPosition(0, (m_size - 1) * m_tileSize - 2);

	// Regenerează liniile verticale negre
	float lineHeight = (m_tileSize + 1) * m_size;
	m_blackVerticalLine1.setSize({ LINE_THICKNESS, lineHeight });
	m_blackVerticalLine1.setFillColor(sf::Color::Black);
	m_blackVerticalLine1.setPosition(m_tileSize, 0);

	m_blackVerticalLine2.setSize({ LINE_THICKNESS, lineHeight });
	m_blackVerticalLine2.setFillColor(sf::Color::Black);
	m_blackVerticalLine2.setPosition((m_size - 1) * m_tileSize - 2, 0);
}

void Board::SetPillarNumber(int pillarNumber)
{
	m_pillarNumberDef = pillarNumber;
}

std::vector<std::tuple<sf::CircleShape, int, int>> Board::getTiles()
{
	return m_tiles;
}

int Board::getTileSize()
{
	return m_tileSize;
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

