#include <SFML/Graphics.hpp>
#include <iostream>


void drawCircle(sf::RenderWindow& window, sf::Vector2f position)
{
	float radius = 50.f;
	float outlineThickness = 5.f;
	sf::CircleShape circle(radius);
	circle.setOutlineThickness(outlineThickness);
	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineColor(sf::Color::Green);
	circle.setOrigin({ radius, radius });
	circle.setPosition(position);

	window.draw(circle);
}

void drawX(sf::RenderWindow& window, sf::Vector2f position)
{
	sf::RectangleShape line({ 100.f, 10.f });
	line.setFillColor(sf::Color::Red);
	line.setRotation(sf::degrees(45));
	line.setOrigin(line.getSize() / 2.f);
	line.setPosition(position);

	sf::RectangleShape line2({ 100.f, 10.f });
	line2.setFillColor(sf::Color::Red);
	line2.setRotation(sf::degrees(-45));
	line2.setOrigin(line2.getSize() / 2.f);
	line2.setPosition(position);

	window.draw(line);
	window.draw(line2);
}

void drawGameGrid(sf::RenderWindow& window)
{
	sf::RectangleShape gridLine;
	gridLine.setFillColor(sf::Color(255, 255, 255, 100));

	// upper lines
	gridLine.setSize({ 2.f,  static_cast<float>(window.getSize().y) });
	gridLine.setOrigin(gridLine.getSize() / 2.f);

	// left line
	gridLine.setPosition({ window.getSize().x / 3.f,window.getSize().y / 2.f });
	window.draw(gridLine);

	// right line
	gridLine.setPosition({ window.getSize().x * 2.f / 3.f, window.getSize().y / 2.f });
	window.draw(gridLine);

	// horizontal lines
	gridLine.setSize({ static_cast<float>(window.getSize().x), 2.f });
	gridLine.setOrigin(gridLine.getSize() / 2.f);

	// upper line
	gridLine.setPosition({ window.getSize().x / 2.f, window.getSize().y / 3.f });
	window.draw(gridLine);

	// bottom line
	gridLine.setPosition({ window.getSize().x / 2.f, window.getSize().y * 2 / 3.f });
	window.draw(gridLine);
}

void drawCursor(sf::RenderWindow& window, sf::Vector2f position)
{
	sf::RectangleShape cursor({ 200.f, 200.f });
	cursor.setFillColor(sf::Color(255, 255, 255, 50));
	cursor.setOrigin(cursor.getSize() / 2.f);
	cursor.setPosition(position);

	window.draw(cursor);
}

void insertLetter(char letter, sf::Vector2f position, char(&state)[3][3])
{
	int i = position.y / 300;
	int j = position.x / 300;

	state[i][j] = letter;

	std::cout << "position: " << position.x << " " << position.y << "\n";
	std::cout << "inserted: " << letter << " on: " << i << " " << j << "\n";
}


int main()
{
	char state[3][3] = {
		{' ', ' ',' '},
		{' ', ' ',' '},
		{' ', ' ',' '}
	};

	int stateLength = sizeof(state) / sizeof(state[0]);

	unsigned int windowDimension = 900.f;

	sf::ContextSettings settings;
	settings.antiAliasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode({ windowDimension, windowDimension }), "TIC TAC TOE", sf::Style::Default, sf::State::Windowed, settings);

	float movementRatio = windowDimension / 3.f;
	sf::Vector2f cursorPosition({ window.getSize().x / 2.f, window.getSize().y / 2.f });

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
			else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				switch (keyPressed->code)
				{
				case sf::Keyboard::Key::Up:
					if (cursorPosition.y > windowDimension / 3.f)
						cursorPosition.y -= movementRatio;
					break;
				case sf::Keyboard::Key::Down:
					if (cursorPosition.y < windowDimension * 2 / 3.f)
						cursorPosition.y += movementRatio;
					break;
				case sf::Keyboard::Key::Right:
					if (cursorPosition.x <= windowDimension * 2 / 3.f)
						cursorPosition.x += movementRatio;
					break;
				case sf::Keyboard::Key::Left:
					if (cursorPosition.x >= windowDimension / 3.f)
						cursorPosition.x -= movementRatio;
					break;
				case sf::Keyboard::Key::O:
					insertLetter('O', cursorPosition, state);
					break;
				case sf::Keyboard::Key::X:
					insertLetter('X', cursorPosition, state);
					break;
				}
			}
		}

		window.clear(sf::Color::Black);

		drawGameGrid(window);
		drawCursor(window, cursorPosition);

		for (int i = 0; i < stateLength; i++)
		{
			for (int j = 0; j < stateLength; j++)
			{
				sf::Vector2f center{
				    j * movementRatio + movementRatio / 2.f,
				    i * movementRatio + movementRatio / 2.f
				};
				if (state[i][j] == 'X')
				{
					drawX(window, center);
				}
				if (state[i][j] == 'O')
				{
					drawCircle(window, center);
				}
			}
		}
		drawX(window, cursorPosition);

		drawCircle(window, cursorPosition);

		window.display();
	}

	return 0;
}