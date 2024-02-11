#include "Dice.h"

Dice* Dice::_instance = nullptr;
//sf::Vector2u Dice::_dices = sf::Vector2u(0, 0);

void Dice::Initialize()
{
	if (_instance == nullptr)
	{
		_instance = this;

		_texture.loadFromFile(DICE_IMAGE_PATH);

		_diceSprite1.setTexture(_texture);
		_diceSprite2.setTexture(_texture);

		_diceSprite1.setPosition(20.f, 20.f);
		_diceSprite2.setPosition(20.f, 20.f + DICE_HEIGHT + 20.f);

		return;
	}
	Debug::LogError("Cannot create Dice. Only one instance possible");
}

void Dice::Roll()
{
	uint16_t dice1 = rand() % 6 + 1;
	uint16_t dice2 = rand() % 6 + 1;

	_instance->_dices.x = dice1;
	_instance->_diceSprite1.setTextureRect(sf::IntRect(DICE_WIDTH * ((dice1 - 1) % 3), DICE_HEIGHT * ((dice1 - 1) / 3), DICE_WIDTH, DICE_HEIGHT));
	_instance->_dices.y = dice2;
	_instance->_diceSprite2.setTextureRect(sf::IntRect(DICE_WIDTH * ((dice2 - 1) % 3), DICE_HEIGHT * ((dice2 - 1) / 3), DICE_WIDTH, DICE_HEIGHT));

	Debug::Log("rolled dices: " + std::to_string(_instance->_dices.x) + " / " + std::to_string(_instance->_dices.y));
}

short Dice::GetPossibleTurnsAmount()
{
	if (_instance->IsDouble())
		return 4;
	return 2;
}

void Dice::Draw(Window* window)
{
	window->Draw(_instance->_diceSprite1);
	window->Draw(_instance->_diceSprite2);
}

