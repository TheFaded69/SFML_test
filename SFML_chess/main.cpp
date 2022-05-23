#include <SFML/Graphics.hpp>
#include "Game.h"
#include "VictoryGame.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(400, 400), "Test Chess", sf::Style::Close | sf::Style::Titlebar);
	window.setFramerateLimit(30);

	Game game;
	game.setPosition(0.f, 0.f);

	sf::Event event;

	while (window.isOpen())
	{

		sf::Vector2i pos = sf::Mouse::getPosition(window);

		//game.AIbot.DoTurn(game.board);

		while (window.pollEvent(event))
		{
			
			if (event.type == sf::Event::Closed) window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::F1)	game.Init();
				if (event.key.code == sf::Keyboard::Escape) window.close();
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.key.code == sf::Mouse::Left)
				{
					game.Turn(pos); //Ход человека начало (выбор фигуры)

					if (!game.user_turn) game.Turn(pos); //Ход человека конец (сам ход) + ход AI
				}
			}

		}

		window.clear();
		window.draw(game);
		window.display();

		if (game.white_victory)
		{
			window.close();
		}
		if (game.black_victory)
		{
			window.close();
		}
	}

	sf::RenderWindow victoryWindow(sf::VideoMode(200, 50), "End game", sf::Style::Close | sf::Style::Titlebar);

	VictoryGame victory;
	
	if (game.black_victory) victory.who_won = 1;
	if (game.white_victory) victory.who_won = 2;

	while (victoryWindow.isOpen())
	{
		while (victoryWindow.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
			{
				victoryWindow.close();
			}
		}
		victoryWindow.clear();
		victoryWindow.draw(victory);
		victoryWindow.display();
	}


}