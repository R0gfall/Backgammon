#include <iostream>

#include "Game.h"

int main()
{
	srand(time(0));
	Game game;

	game.Initialize();

	while (game.IsOpened())
	{
		game.Update();
		game.Draw();
	}
}
