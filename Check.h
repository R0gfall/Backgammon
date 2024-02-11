#pragma once

#include <SFML/Graphics.hpp>

#include "GlobalDefinitions.h"

#include "Window.h"


const short CHECK_WIDTH = 60;
const short CHECK_HEIGHT = 60;

//Класс шашки
//Хранит в себе спрайт и тип шашки
class Check
{
public:
	//Конструктор
	Check(CheckType type);

	//Установка позиции шашки в координатах окна
	void SetPosition(sf::Vector2f position);

	void Draw(Window* window);

	//Возвращает тип шашки
	CheckType GetType() { return _type; }
private:
	sf::Texture _texture;
	sf::Sprite _sprite;

	sf::IntRect _textureRects[3];

	CheckType _type;
};

