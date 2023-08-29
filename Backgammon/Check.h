#pragma once

#include <SFML/Graphics.hpp>

#include "GlobalDefinitions.h"

#include "Window.h"


const short CHECK_WIDTH = 60;
const short CHECK_HEIGHT = 60;

class Check
{
public:
	Check(CheckType type);

	void SetPosition(sf::Vector2f position);

	void Draw(Window* window);

	CheckType GetType() { return _type; }
private:
	sf::Texture _texture;
	sf::Sprite _sprite;

	sf::IntRect _textureRects[3];

	CheckType _type;
};

