#include "game_map.h"

#include <iostream>

GameMap::GameMap(const std::array<int, kWidth * kHeight>& game_map):
game_map_(game_map)
{
	
}

GameMap::~GameMap()
{
	//std::cout << "Map Destroy" << std::endl;
}
