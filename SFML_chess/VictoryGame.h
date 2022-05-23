#pragma once
#include <SFML/Graphics.hpp>

class VictoryGame: public sf::Drawable, public sf::Transformable
{
public:
	int who_won;

	VictoryGame();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

