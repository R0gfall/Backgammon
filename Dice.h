#pragma once

#include "GlobalDefinitions.h"

#include "Debug.h"

const short DICE_WIDTH = 200;
const short DICE_HEIGHT = 200;

//Класс игральных костей
class Dice
{
public:
	//Метод инициализации (обязан вызываться единственный раз)
	void Initialize();

	//Метод чтобы бросить кости
	static void Roll();
	//Возвращает значение костей
	static sf::Vector2u GetDices() { return _instance->_dices; }
	//Проверка, дубль ли на костях
	static short IsDouble() { return _instance->_dices.x == _instance->_dices.y; }
	//Возвращает количество возможных ходов в зависимости от дубля
	static short GetPossibleTurnsAmount();
	static void Draw(Window* window);

private:
	static Dice* _instance;
	sf::Vector2u _dices;
	sf::Texture _texture;
	sf::Sprite _diceSprite1;
	sf::Sprite _diceSprite2;
};

