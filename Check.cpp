#include "Check.h"

Check::Check(CheckType type)
{
	_type = type;

	_texture.loadFromFile(CHECK_IMAGE_PATH);
	_sprite.setTexture(_texture);

	_textureRects[0] = sf::IntRect(0, 0, CHECK_WIDTH, CHECK_HEIGHT);
	_textureRects[1] = sf::IntRect(CHECK_WIDTH, 0, CHECK_WIDTH, CHECK_HEIGHT);
	_textureRects[2] = sf::IntRect(CHECK_WIDTH * 2, 0, CHECK_WIDTH, CHECK_HEIGHT);

	_sprite.setTextureRect(_textureRects[(short)type]);
}

void Check::SetPosition(sf::Vector2f position)
{
	_sprite.setPosition(position);
}

void Check::Draw(Window* window)
{
	window->Draw(_sprite);
}
