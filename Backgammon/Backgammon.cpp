#include <iostream>

#include "Game.h"

int main()
{
	srand(NULL);
	Game game;

	game.Initialize();

	while (game.IsOpened())
	{
		game.Update();
		game.Draw();
	}
}
