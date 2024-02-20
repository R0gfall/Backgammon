#include <iostream>
#include "Game.h"



int main()
{
	srand(time(NULL));
	//srand(NULL);
	Game game;

	game.Initialize();

	while (game.IsOpened())
	{
		game.Update();
		game.Draw();
	}
	
}
