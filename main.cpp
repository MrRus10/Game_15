#include "game_15.h"
#include<random>
using namespace std;

int main() {
	sf::RenderWindow window(sf::VideoMode(600, 600), "FifteenGame");
	window.setFramerateLimit(60);

	sf::Font font;
	font.loadFromFile("C:/Windows/Fonts/calibri.ttf");
	
	sf::Text text("F2 - New Game / Esc - Exit / Arrow Keys - Move Tile", font, 20);
	text.setFillColor(sf::Color::Cyan);
	text.setPosition(5.f, 5.f);

	FifteenGame game;
	game.setPosition(50.f, 50.f);
	
	sf::Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) window.close();
				if (event.key.code == sf::Keyboard::Left) game.Move(Direction::Right);
				if (event.key.code == sf::Keyboard::Right) game.Move(Direction::Left);
				if (event.key.code == sf::Keyboard::Up) game.Move(Direction::Down);
				if (event.key.code == sf::Keyboard::Down) game.Move(Direction::Up);
				if (event.key.code == sf::Keyboard::F2) {
					game.FillWithRandomUniqueNums();
				}
			}
		}
 		window.clear();
		window.draw(game);
		window.draw(text);
		window.display();
	}
	return 0;
}