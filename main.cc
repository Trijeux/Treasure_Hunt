#include "game.h"
#include "gameSFML.h"

// ReSharper disable once CppInconsistentNaming
constexpr bool kSFML = true;

int main()
{
	if (kSFML)
	{
		GameSFML game_sfml;

		game_sfml.GameLoop();
	}
	else
	{
		Game game;

		game.GameLoop();
	}
}
