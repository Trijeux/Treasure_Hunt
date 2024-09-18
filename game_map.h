#ifndef MAP_H
#define MAP_H

#include <array>

constexpr int kWidth = 5; //L
constexpr int kHeight = 5; //H


class GameMap
{
public:
	explicit GameMap(const std::array<int, kWidth* kHeight>& game_map);

protected:
private:
	std::array<int, kWidth* kHeight> game_map_;
};

#endif // MAP_H
