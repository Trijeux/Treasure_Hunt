#ifndef GAMESFML_H
#define GAMESFML_H
#include <array>
#include <SFML/Graphics.hpp>


constexpr int kSHeight = 5;
constexpr int kSWidth = 5;

enum class TileSfml
{
	kNoDig,
	kNothing,
	kChest,
	kMax
};

// ReSharper disable once CppInconsistentNaming
class GameSFML
{
public:
	GameSFML();
	void ClickTileMap(sf::Event event);
	void DrawMap();
	void EndGame();
	void DrawGame();
	void GameLoop();
private:
	std::array<TileSfml,kSHeight*kSWidth > array_map_;

	sf::RenderWindow window_game_;

	sf::RenderWindow window_count_try_;

	sf::Font font_;
	sf::Text text_;

	sf::Texture texture_mouse_;
	sf::Sprite sprite_mouse_;

	sf::Texture texture_sand_;
	sf::Sprite sprite_sand_;

	sf::Texture texture_sand_dig_;
	sf::Sprite sprite_sand_dig_;

	sf::Texture texture_chest_;
	sf::Sprite sprite_chest_;

	int chest_;

	int try_;

	bool chest_find_ = false;
	bool chest_no_find_ = false;

	void RandChest();
};

#endif // GAMESFML_H
