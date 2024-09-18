#include "game.h"

#include <iostream>

void Game::GameLoop()
{
	Display();
}

void Game::Display()
{
	for (int y = 0; y < kHeight; y++)
	{
		for (int x = 0; x < kWidth; x++)
		{
			int idx = y * kWidth + x;


		}
	}
}
