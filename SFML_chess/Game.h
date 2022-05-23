#pragma once
#include <SFML/Graphics.hpp>
#include "Field.h"
#include "AIGame.h"

class Game: public sf::Drawable, public sf::Transformable
{
public:
	Field board[SIZE][SIZE];

	bool white_victory = false;
	bool black_victory = false;
	bool user_turn = true;
	bool chose_figure = false;

private:
	int chose_pos_x = 0;
	int chose_pos_y = 0;

	sf::Image white_figure;
	sf::Image black_figure;
public:
	AIGame AIbot;

public:
	Game();
	void Init();
	void Turn(sf::Vector2i position);
	void CheckWinner();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

