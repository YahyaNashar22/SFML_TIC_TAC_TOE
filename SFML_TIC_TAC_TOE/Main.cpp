#include <SFML/Graphics.hpp>


void drawCircle(sf::RenderWindow & window)
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

void drawX(sf::RenderWindow & window)
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

		drawX(window);

		window.display();
	}

	return 0;
}