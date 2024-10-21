#include "gameSFML.h"

#include <iostream>

GameSFML::GameSFML()
{
	texture_mouse_.loadFromFile("assets/cursor/Shovel.png");
	sprite_mouse_.setTexture(texture_mouse_);
	sprite_mouse_.setOrigin(texture_mouse_.getSize().x / 2, texture_mouse_.getSize().y / 2);  // NOLINT(bugprone-integer-division, bugprone-narrowing-conversions, cppcoreguidelines-narrowing-conversions)

	texture_sand_.loadFromFile("assets/sprite/Sand.png");
	sprite_sand_.setTexture(texture_sand_);
	sprite_sand_.setScale(2, 2);

	// ReSharper disable once StringLiteralTypo
	texture_sand_dig_.loadFromFile("assets/sprite/Sand_Dige.png");
	sprite_sand_dig_.setTexture(texture_sand_dig_);
	sprite_sand_dig_.setScale(2, 2);

	texture_chest_.loadFromFile("assets/sprite/Chest.png");
	sprite_chest_.setTexture(texture_chest_);
	sprite_chest_.setScale(2, 2);

	window_game_.create(sf::VideoMode(sprite_sand_.getGlobalBounds().width * kSWidth, sprite_sand_.getGlobalBounds().height * kSHeight), "Treasure Hunt");

	window_count_try_.create(sf::VideoMode(250, 250), "Try Count");
	window_count_try_.setPosition(sf::Vector2i(window_game_.getPosition().x * 2, window_game_.getPosition().y));

	window_game_.setMouseCursorVisible(false);


	font_.loadFromFile("assets/font/Crang.ttf");
	text_.setFont(font_);

	try_ = 10;

	array_map_.fill(TileSfml::kNoDig);

	srand(time(NULL));

	RandChest();
}

void GameSFML::ClickTileMap(sf::Event event)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
			

		const sf::Vector2i mouse_pos = sf::Mouse::getPosition(window_game_);


		const int x = mouse_pos.x / (texture_sand_.getSize().x * sprite_sand_.getScale().x);
		const int y = mouse_pos.y / (texture_sand_.getSize().y * sprite_sand_.getScale().y);

		if (x >= 0 && x < kSWidth && y >= 0 && y < kSHeight)
		{
			const int idx = y * kSWidth + x;


			if (array_map_.at(idx) == TileSfml::kNoDig)
			{
				try_--;
				if (idx == chest_)
				{
					array_map_.at(idx) = TileSfml::kChest;
					chest_find_ = true;
				}
				else
					array_map_.at(idx) = TileSfml::kNothing;
			}
		}
	}
}

void GameSFML::DrawMap()
{
	for (int y = 0; y < kSHeight; y++)
	{
		for (int x = 0; x < kSWidth; x++)
		{
			const int idx = y * kSWidth + x;

			switch (array_map_.at(idx))
			{
			case TileSfml::kNoDig:
				{
					sprite_sand_.setPosition((x * texture_sand_.getSize().x) * sprite_sand_.getScale().x, (y * texture_sand_.getSize().y) * sprite_sand_.getScale().y);
					window_game_.draw(sprite_sand_);
				}
				break;
			case TileSfml::kNothing:
				{
					sprite_sand_dig_.setPosition((x * texture_sand_dig_.getSize().x) * sprite_sand_dig_.getScale().x, (y * texture_sand_dig_.getSize().y) * sprite_sand_dig_.getScale().y);
					window_game_.draw(sprite_sand_dig_);
				}
				break;
			case TileSfml::kChest:
				{
					sprite_chest_.setPosition((x * texture_chest_.getSize().x) * sprite_chest_.getScale().x, (y * texture_chest_.getSize().y) * sprite_chest_.getScale().y);
					window_game_.draw(sprite_chest_);
				}
				break;
			}
		}
	}
}

void GameSFML::EndGame()
{
	text_.setFillColor(sf::Color::Red);

	if (chest_find_)
	{
		text_.setString("You Win\nQuit for End");
	}

	if (chest_no_find_)
	{
		text_.setString("You Lose\nQuit for End");
	}

	text_.setOrigin(text_.getCharacterSize() / 2, text_.getCharacterSize() / 2);
	text_.setScale(2, 2);
	text_.setPosition((window_game_.getSize().x / 2) - 190, (window_game_.getSize().y / 2) - 75);
	window_game_.draw(text_);
}

void GameSFML::DrawGame()
{
	window_game_.clear();
	window_count_try_.clear();

	DrawMap();

	text_.setString(std::to_string(try_));
	text_.setOrigin(text_.getCharacterSize() / 2, text_.getCharacterSize() / 2);
	text_.setScale(5, 5);
	text_.setPosition(window_count_try_.getSize().x / 2, window_count_try_.getSize().y / 2);

	window_count_try_.draw(text_);

	if (chest_find_ || chest_no_find_)
	{
		EndGame();
	}

	sprite_mouse_.setPosition(sf::Mouse::getPosition(window_game_).x, sf::Mouse::getPosition(window_game_).y);  // NOLINT(bugprone-narrowing-conversions, cppcoreguidelines-narrowing-conversions)
	window_game_.draw(sprite_mouse_);
	window_game_.display();
	window_count_try_.display();
}

void GameSFML::GameLoop()
{
	while (window_game_.isOpen())
	{
		sf::Event event;
		while (window_game_.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window_game_.close();
				window_count_try_.close();
				exit(0);
			}

			ClickTileMap(event);
		}

		do
		{
			while (window_game_.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window_game_.close();
					window_count_try_.close();
					exit(0);
				}
			}

			DrawGame();
			
		}
		while (chest_find_ || chest_no_find_);

		if (try_ <= 0)
		{
			chest_no_find_ = true;
		}
	}
}

void GameSFML::RandChest()
{
	chest_ = rand() % array_map_.size();
}

