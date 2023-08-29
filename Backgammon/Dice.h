#pragma once

#include "GlobalDefinitions.h"

#include "Debug.h"

const short DICE_WIDTH = 200;
const short DICE_HEIGHT = 200;

class Dice
{
public:

	void Initialize();

	static void Roll();
	static sf::Vector2u GetDices() { return _instance->_dices; }
	static short IsDouble() { return _instance->_dices.x == _instance->_dices.y; }
	static short GetPossibleTurnsAmount();
	static void Draw(Window* window);

private:
	static Dice* _instance;
	sf::Vector2u _dices;
	sf::Texture _texture;
	sf::Sprite _diceSprite1;
	sf::Sprite _diceSprite2;
};

