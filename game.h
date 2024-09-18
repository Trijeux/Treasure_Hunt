#ifndef GAME_H
#define GAME_H

#include "game_map.h"

class Game
{
public:
	Game() = default;

	void GameLoop();
protected:
private:

	GameMap game_map_;

	enum class Tile
	{
		kNoDig,
		kNothing,
		kTreasure,
		kMax
	};

	
	void ChoicePlayer();
	void Display();
};

#endif // GAME_H
