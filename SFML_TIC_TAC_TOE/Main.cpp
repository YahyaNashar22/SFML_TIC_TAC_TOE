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

		drawCircle(window);

		window.display();
	}

	return 0;
}