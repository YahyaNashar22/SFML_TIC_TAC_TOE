#include <SFML/Graphics.hpp>
#include <iostream>


void drawCircle(sf::RenderWindow& window)
{
	float radius = 50.f;
	float outlineThickness = 5.f;
	sf::CircleShape circle(radius);
	circle.setOutlineThickness(outlineThickness);
	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineColor(sf::Color::Green);
	circle.setOrigin({ radius, radius });
	circle.setPosition({ 400, 300 });

	window.draw(circle);
}

void drawX(sf::RenderWindow& window)
{
	sf::RectangleShape line({ 100.f, 10.f });
	line.setFillColor(sf::Color::Red);
	line.setRotation(sf::degrees(45));
	line.setOrigin(line.getSize() / 2.f);
	line.setPosition({ 400, 300 });

	sf::RectangleShape line2({ 100.f, 10.f });
	line2.setFillColor(sf::Color::Red);
	line2.setRotation(sf::degrees(-45));
	line2.setOrigin(line2.getSize() / 2.f);
	line2.setPosition({ 400, 300 });

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
	gridLine.setPosition({window.getSize().x / 3.f,window.getSize().y / 2.f});
	window.draw(gridLine);

	// right line
	gridLine.setPosition({ window.getSize().x * 2.f / 3.f, window.getSize().y / 2.f});
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

int main()
{
	sf::ContextSettings settings;
	settings.antiAliasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "TIC TAC TOE", sf::Style::Default, sf::State::Windowed, settings);

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}

		window.clear(sf::Color::Black);

		drawGameGrid(window);

		window.display();
	}

	return 0;
}