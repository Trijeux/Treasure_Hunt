#ifndef GAME_H
#define GAME_H
#include <array>

constexpr int kHeight = 5;
constexpr int kWidth = 5;

class Game
{
public:
	Game();

	void GameLoop();

protected:
private:
	bool end_game_ = false;
	bool chest_find_ = false;
	bool valid_pos_ = false;
	bool retry_ = false;

	int chest_;

	int try_;

	enum class Tile
	{
		kNoDig,
		kNothing,
		kChest,
		kMax
	};

	std::array<Tile, kHeight* kWidth> array_map_;
	int ChoicePlayer(char);
	bool CheckChest(int,int);
	void RandChest();
	void Display() const;
	void Retry();
};

#endif // GAME_H
