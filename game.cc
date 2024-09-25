#include "game.h"

#include <algorithm>
#include <iostream>
#include <string>

Game::Game()
{
	// Start of the game
	std::cout << "Hello, welcome to the treasure hunt" << std::endl;
	std::cout << "your goal is to find the treasure by choosing the row and the column" << std::endl << std::endl;

	srand(time(NULL));
}

void Game::GameLoop()
{
	do
	{
		array_map_.fill(Tile::kNoDig);
		RandChest();
		try_ = 10;
		end_game_ = false;
		//std::cout << chest_ << std::endl;
		do
		{
			std::cout << "number of tries : " << try_ << std::endl;
			Display();
			do
			{
				int w = ChoicePlayer('w');
				int h = ChoicePlayer('h');
				valid_pos_ = CheckChest(h - 1, w - 1);
			} while (!valid_pos_);
			try_--;

			if (try_ <= 0)
			{
				end_game_ = true;
			}

			system("cls");
		} while (!end_game_);

		if (chest_find_)
		{
			std::cout << "Number of tests remain : " << try_ << std::endl;
			Display();
			std::cout << "Well done you won" << std::endl;
		}
		else
		{
			std::cout << "Number of tests remain : " << try_ << std::endl;
			Display();
			std::cout << "Well done you lose" << std::endl;
		}

		Retry();
	}
	while (retry_);
}

int Game::ChoicePlayer(char h_or_w)
{
	int height = 0;
	int width = 0;

	std::string input_player;

	bool valid_input;
	bool valid_number;

	do
	{
		do
		{
			valid_input = true;
			valid_number = true;
			if (h_or_w == 'h')
			{
				std::cout << "Between the column " << 1 << "-" << kWidth << std::endl;
			}
			else if (h_or_w == 'w')
			{
				std::cout << "Between the row" << 1 << "-" << kHeight << std::endl;
			}
			std::getline(std::cin, input_player);

			// Check if it's a number or not
			if (input_player.length() == 0 || !std::all_of(input_player.begin(), input_player.end(), ::isdigit))
			{
				system("cls");
				std::cout << input_player << " is not a number" << std::endl;
				Display();
				valid_input = false;
			}
			if (valid_input)
			{
				// Checks if number is between 1 and array size
				if (h_or_w == 'h')
				{
					height = std::stoi(input_player);
					valid_input = true;
				}
				else if (h_or_w == 'w')
				{
					width = std::stoi(input_player);
					valid_input = true;
				}

				if ((height > kHeight || height < 1) && h_or_w == 'h')
				{
					system("cls");
					valid_number = false;
					std::cout << "It is not a number between 1-" << kWidth << std::endl;
					Display();
				}
				else if ((width > kWidth || width < 1) && h_or_w == 'w')
				{
					system("cls");
					valid_number = false;
					std::cout << "It is not a number between 1-" << kHeight << std::endl;
					Display();
				}
			}
		} while (!valid_number);

	} while (!valid_input);

	if (h_or_w == 'h')
	{
		return height;
	}
	if (h_or_w == 'w')
	{
		return width;
	}
}

bool Game::CheckChest(const int height, const int width)
{
	const int idx = width * kWidth + height;

	if (array_map_.at(idx) == Tile::kNothing)
	{
		system("cls");
		std::cout << "The chosen box has already been dug!!" << std::endl;
		Display();
		return false;
	}
	if (idx == chest_)
	{
		array_map_.at(idx) = Tile::kChest;
		end_game_ = true;
		chest_find_ = true;
		return true;
	}

	array_map_.at(idx) = Tile::kNothing;
	return true;
}

void Game::RandChest()
{
	chest_ = rand() % array_map_.size();
}

void Game::Display() const
{
	std::cout << std::endl;

	for (int height = 0; height < kHeight; height++)
	{
		for (int width = 0; width < kWidth; width++)
		{
			const int idx = height * kWidth + width;

			switch (array_map_.at(idx))
			{
			case Tile::kNoDig:
			{
				std::cout << "# ";
			}
			break;
			case Tile::kNothing:
			{
				std::cout << "X ";
			}
			break;
			case Tile::kChest:
			{
				std::cout << "$ ";
			}
			break;
			case Tile::kMax:
			{
				std::cout << "ERROR ";
			}
			break;
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Game::Retry()
{
	char player_choice;
	bool valid_input = false;
	do
	{
		std::cout << "Do you want to fight again ? (Y/y) (N/n) ";

		std::cin >> player_choice;

		if (player_choice == 'n' || player_choice == 'N')
		{
			retry_ = false;
			valid_input = true;
		}
		else if (player_choice == 'y' || player_choice == 'Y')
		{
			retry_ = true;
			valid_input = true;
		}
		else
		{
			std::cout << "Input is invalid" << std::endl;
		}

		system("cls");
	} while (!valid_input);
}
