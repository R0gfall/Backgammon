#pragma once

#include "SFML/Graphics.hpp"
#include "Bitmask.h"

using Keyboard = sf::Keyboard;

//Класс для обработки ввода
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

	//Обновление каждый кадр
	static void Update();

	//Проверка, зажата ли клавиша
	static bool IsKeyPressed(Key keycode);
	//Проверка, нажата ли клавиша
	static bool IsKeyDown(Key keycode);
	//Проверка, отпущена ли клавиша
	static bool IsKeyUp(Key keycode);

private:
	//Битовая маска на текущие клавиши
	static Bitmask _thisFrameKeys;
	//Битовая маска на клавиши прошлого кадра
	static Bitmask _lastFrameKeys;
};