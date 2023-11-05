#include "Board.h"
#include "Pillar.h"
Board::Board()
	:m_size(24),
	m_tileSize(30),
	m_boardSize1(18),
	m_boardSize2(24),
	m_boardSize3(30)
{
	button18x18.setSize({ 100, 50 });
	button18x18.setFillColor(sf::Color::White);
	button18x18.setPosition(50, 80); // Ajustează poziția după necesitate

	button24x24.setSize({ 100, 50 });
	button24x24.setFillColor(sf::Color::White);
	button24x24.setPosition(50, 140); // Ajustează poziția după necesitate

	button30x30.setSize({ 100, 50 });
	button30x30.setFillColor(sf::Color::White);
	button30x30.setPosition(50, 200);

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

	// Set its color to rgb(247, 255, 208)
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
			m_tiles.push_back(tile);
			BoardWindow.draw(tile);
		}
	}

	// Declare the mousePosition and mousePostionFloat variables.
	sf::Vector2i mousePosition;
	sf::Vector2f mousePositionFloat;

	// Get the position of the mouse.
	mousePosition = sf::Mouse::getPosition(BoardWindow);

	// Convert the mousePosition to a sf::Vector2f object.
	mousePositionFloat = sf::Vector2f(mousePosition.x, mousePosition.y);

	// Check if the mouse is over a cell.
	int x = mousePositionFloat.x / m_tileSize;
	int y = mousePositionFloat.y / m_tileSize;

	for (auto& tile : m_tiles)
	{
		if (tile.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
		{
			// Create a new pillar.
			Pillar pillar(x * m_tileSize, y * m_tileSize, sf::Color::Red);
			pillar.setPosition(tile.getPosition());
			pillar.Draw(BoardWindow);
		}
	}

	// Position of the red and black lines showing the borders of each player
	m_redHorizontalLine1.setPosition(offsetX - m_tileSize * 0.8, offsetY + DOT_RADIUS * 3.5);
	m_redHorizontalLine2.setPosition(offsetX - m_tileSize * 0.8, offsetY + (m_size - 1) * m_tileSize - DOT_RADIUS * 2);
	m_blackVerticalLine1.setPosition(offsetX + DOT_RADIUS * 3.5, offsetY - m_tileSize * 0.8);
	m_blackVerticalLine2.setPosition(offsetX + (m_size - 1) * m_tileSize - DOT_RADIUS * 2, offsetY - m_tileSize * 0.8);
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
			m_tiles.push_back(tile);
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

void Board::DrawSettingsButtons(sf::RenderWindow& settingsWindow)
{
	sf::Text text18x18;
	sf::Font settingsfont;

	settingsfont.loadFromFile("ARIAL.TTF");
	text18x18.setFont(settingsfont); // Set the font to our text
	text18x18.setString("18x18"); // Set the button label text
	text18x18.setCharacterSize(24); // Set the text size
	text18x18.setFillColor(sf::Color::Black); // Set the text color

	sf::FloatRect textRect = text18x18.getLocalBounds();

	// Position the text relative to the button
	text18x18.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	text18x18.setPosition(sf::Vector2f(button18x18.getPosition().x + button18x18.getSize().x / 2.0f, button18x18.getPosition().y + button18x18.getSize().y / 2.0f));

	sf::Text text24x24 = text18x18;

	text24x24.setString("24x24");
	// Position the text relative to the button
	text24x24.setPosition(sf::Vector2f(button24x24.getPosition().x + button24x24.getSize().x / 2.0f, button24x24.getPosition().y + button24x24.getSize().y / 2.0f));

	sf::Text text30x30 = text18x18;

	text30x30.setString("30x30");
	// Position the text relative to the button
	text30x30.setPosition(sf::Vector2f(button30x30.getPosition().x + button30x30.getSize().x / 2.0f, button30x30.getPosition().y + button30x30.getSize().y / 2.0f));

	settingsWindow.draw(button18x18);
	settingsWindow.draw(text18x18);
	settingsWindow.draw(button24x24);
	settingsWindow.draw(text24x24);
	settingsWindow.draw(button30x30);
	settingsWindow.draw(text30x30);
}

