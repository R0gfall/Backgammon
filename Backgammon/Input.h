#pragma once

#include "SFML/Graphics.hpp"
#include "Bitmask.h"

using Keyboard = sf::Keyboard;

class Input
{
public:
	enum class Key
	{
		None = 0,
		Left,
		Right,
		Up,
		Down,
		Horizontal,
		Vertical,
		Space,
		Esc,
		LBracket,
		RBracket,
		LShift,
		RShift,
		LMouseButton,
		RMouseButton,
		Q,
		W,
		E,
		R,
		T,
		Y,
		U,
		I,
		O,
		P,
		A,
		S,
		D,
		F,
		G,
		H,
		J,
		K,
		L,
		Z,
		X,
		C,
		V,
		B,
		N,
		M,

	};

	static void Update();

	static bool IsKeyPressed(Key keycode);
	static bool IsKeyDown(Key keycode);
	static bool IsKeyUp(Key keycode);

private:
	static Bitmask _thisFrameKeys;
	static Bitmask _lastFrameKeys;
};