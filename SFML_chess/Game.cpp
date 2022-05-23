#include "Game.h"
#include <iostream>

Game::Game()
{
	if (!white_figure.loadFromFile("whiteFigure.png")) 
		throw;
	if (!black_figure.loadFromFile("blackFigure.png")) 
		throw;

	Init();
}

void Game::Init()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if ((i < 3) && (j < 3))
			{
				board[i][j].isBusyBlack = true;
				board[i][j].isBusyWhite = false;
				board[i][j].isFree = false;
			}
			else if ((i > 4) && (j > 4))
			{
				board[i][j].isBusyWhite = true;
				board[i][j].isBusyBlack = false;
				board[i][j].isFree = false;
			}
			else
			{
				board[i][j].isFree = true;
				board[i][j].isBusyWhite = false;
				board[i][j].isBusyBlack = false;
			}
		}
	}

	AIbot.turn_count = 0;
}

void Game::Turn(sf::Vector2i position)
{
	if (user_turn)
	{
		//std::cout << position.x << " " << position.y << std::endl;

		if (!chose_figure)
		{
			if (board[position.x / FIELD_SIZE][position.y / FIELD_SIZE].isBusyWhite)
			{
				chose_figure = true;

				chose_pos_x = position.x / FIELD_SIZE;
				chose_pos_y = position.y / FIELD_SIZE;

				//std::cout << chose_pos_x << " " << chose_pos_y << std::endl;
			}
		}
		else
		{
			if ((board[position.x / FIELD_SIZE][position.y / FIELD_SIZE].isFree) && (position.y / FIELD_SIZE - chose_pos_y >= -1) && (position.y / FIELD_SIZE - chose_pos_y <= 1) && (position.x / FIELD_SIZE - chose_pos_x <= 1) && (position.x / FIELD_SIZE - chose_pos_x >= -1) && (position.x / FIELD_SIZE - chose_pos_x + position.y / FIELD_SIZE - chose_pos_y <= 1) && (position.x / FIELD_SIZE - chose_pos_x + position.y / FIELD_SIZE - chose_pos_y >= -1)&&(position.x / FIELD_SIZE - chose_pos_x + position.y / FIELD_SIZE - chose_pos_y!=0))
			{
				board[position.x / FIELD_SIZE][position.y / FIELD_SIZE].isBusyWhite = true;
				board[position.x / FIELD_SIZE][position.y / FIELD_SIZE].isFree = false;

				board[chose_pos_x][chose_pos_y].isBusyWhite = false;
				board[chose_pos_x][chose_pos_y].isFree = true;

				user_turn = false;
			}
			chose_figure = false;
		}
		CheckWinner();
	}
	else
	{
		AIbot.DoTurn(board);

		user_turn = true;
		CheckWinner();
	}

	//AIbot.DoTurn(board);
}

void Game::CheckWinner()
{
	if ((board[0][0].isBusyWhite) && (board[0][1].isBusyWhite) && (board[0][2].isBusyWhite) && (board[1][0].isBusyWhite) && (board[1][1].isBusyWhite) && (board[1][2].isBusyWhite) && (board[2][0].isBusyWhite) && (board[2][1].isBusyWhite) && (board[2][2].isBusyWhite)) white_victory = true;
	if ((board[5][5].isBusyBlack) && (board[5][6].isBusyBlack) && (board[5][7].isBusyBlack) && (board[6][5].isBusyBlack) && (board[6][6].isBusyBlack) && (board[6][7].isBusyBlack) && (board[7][5].isBusyBlack) && (board[7][6].isBusyBlack) && (board[7][7].isBusyBlack)) black_victory = true;
}

void Game::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	sf::Color white_color = sf::Color(200, 200, 200);     //белый
	sf::Color grey_color = sf::Color(80, 80, 80);		 //серый
	sf::Color black_color = sf::Color(0, 0, 0);				 //черный

	sf::Texture texture_white_figure;
	sf::Texture texture_black_figure;
	sf::Sprite sprite_white_figure;
	sf::Sprite sprite_black_figure;

	texture_black_figure.loadFromImage(black_figure);
	texture_white_figure.loadFromImage(white_figure);

	sprite_black_figure.setTexture(texture_black_figure);
	sprite_white_figure.setTexture(texture_white_figure);

	sf::RectangleShape shape(sf::Vector2f(FIELD_SIZE, FIELD_SIZE));

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if ((i + j) % 2 == 0)
			{
				shape.setFillColor(white_color);		
			}
			else
			{
				shape.setFillColor(grey_color);
			}


			sf::Vector2f field_position(i%SIZE*FIELD_SIZE, j%SIZE*FIELD_SIZE);
			
			shape.setPosition(field_position);

			target.draw(shape, states);

			if (board[i][j].isBusyBlack)
			{
				sf::Vector2f position(i%SIZE*FIELD_SIZE, j%SIZE*FIELD_SIZE);

				sprite_black_figure.setPosition(position);

				target.draw(sprite_black_figure, states);
			}
			if (board[i][j].isBusyWhite)
			{
				sf::Vector2f position(i%SIZE*FIELD_SIZE, j%SIZE*FIELD_SIZE);

				sprite_white_figure.setPosition(position);

				target.draw(sprite_white_figure, states);
			}

		}
	}

	if (chose_figure)
	{
		sf::RectangleShape chose_shape(sf::Vector2f(FIELD_SIZE, FIELD_SIZE));
		sf::Vector2f chose_field_position(chose_pos_x%SIZE*FIELD_SIZE, chose_pos_y%SIZE*FIELD_SIZE);

		chose_shape.setOutlineColor(sf::Color::Green);
		chose_shape.setOutlineThickness(2.f);
		chose_shape.setPosition(chose_field_position);
		chose_shape.setFillColor(sf::Color::Transparent);

		target.draw(chose_shape, states);
	}

}
