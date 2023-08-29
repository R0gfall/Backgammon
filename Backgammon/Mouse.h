#pragma once

#include <SFML/Graphics.hpp>
#include "Window.h"

#include "Bitmask.h"

class Mouse
{
public:
	enum class Key
	{
		LMouseButton = 1,
		RMouseButton = 2,

	};

	static sf::Vector2f GetRelativePosition();

	static void Update();

	static bool IsLMBDown(Key keycode);
	static bool IsLMBPressed(Key keycode);
	static bool IsLMBUp(Key keycode);

private:
	static Bitmask _lastFrameKeys;
	static Bitmask _thisFrameKeys;
};

