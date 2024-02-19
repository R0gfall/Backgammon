#include <iostream>

#include "Game.h"

int main()
{
	srand(NULL);
	//srand(time(0));
	// это строка
	Game game;

	game.Initialize();

	while (game.IsOpened())
	{
		game.Update();
		game.Draw();
	}
}
