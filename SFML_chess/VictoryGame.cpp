#include "VictoryGame.h"

VictoryGame::VictoryGame()
{

}

void VictoryGame::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	sf::Font font;
	font.loadFromFile("calibri.ttf");

	sf::Text text("", font, 30);

	if (who_won == 1) //black
	{
		text.setString("Black won!!!");
	}
	if (who_won == 2) //white
	{
		text.setString("White won!!!");
	}

	target.draw(text, states);
}
