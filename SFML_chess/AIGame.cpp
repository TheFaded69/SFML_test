#include "AIGame.h"
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

AIGame::AIGame()
{
	arr = new int*[SIZE];
	for (int i = 0; i < SIZE; i++) arr[i] = new int[SIZE];

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if ((i <= 2) && (j <= 2)) arr[i][j] = 1;
			else if ((i >= 5) && (j >= 5)) arr[i][j] = 2;
			else arr[i][j] = 0;;
		}
	}
}

AIGame::~AIGame()
{
	for (int i = 0; i < SIZE; i++) delete[] arr[i];
	delete[] arr;
}

void AIGame::UpdateArr(Field(&field)[SIZE][SIZE])
{
	for (int j = 0; j < SIZE; j++)
	{
		for (int i = 0; i < SIZE; i++)
		{
			if (field[i][j].isBusyBlack)
			{
				arr[i][j] = 1;
			}
			else if (field[i][j].isBusyWhite)
			{
				arr[i][j] = 2;
			}
			else if (field[i][j].isFree)
			{
				arr[i][j] = 0;
			}
		}
	}
}

void AIGame::DoTurn(Field(&field)[SIZE][SIZE])
{
	this->UpdateArr(field);
	this->SearchBestTurn(field);
}

void AIGame::SearchBestTurn(Field(&field)[SIZE][SIZE]) //ѕервые 4 хода заскриптованы хардкодом, возможно надо сделать несколько скриптов дл€ 4ых кодов, которые будут выбиратьс€ нарандом
{
	/*switch (turn_count)
	{
	case 0:
		MoveFuncBlack(field, 2, 2, 2, 3);
		break;
	case 1:
		MoveFuncBlack(field, 2, 1, 3, 1);
		break;
	case 2:
		MoveFuncBlack(field, 1, 2, 1, 3);
		break;
	case 3:
		MoveFuncBlack(field, 1, 1, 2, 1);
		break;
	default:
		CalculateBestTurn(arr);
		MoveFuncBlack(field, from_x, from_y, to_x, to_y);
		break;
	}*/

	CalculateBestTurn(arr);
	MoveFuncBlack(field, from_x, from_y, to_x, to_y);
	from_x = from_y = to_x = to_y = 0;
}

int AIGame::CalculateBestTurn(int** arr)
{
	int count_AI_turn = 0;
	int count_player_turn = 0;
	int count_AI_good_turn = 0;
	int count_player_good_turn = 0;

	//std::multimap<std::pair<int, int>, std::pair<int, int>> mapBlack; // люч - пара координат фигуры, значение - пары координат возможных ходов
	//std::multimap<std::pair<int, int>, std::pair<int, int>> mapWhite;

	std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> mapBlack; // люч - пара координат фигуры, значение - вектор координат возможных ходов
	std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> mapWhite;

	//÷икл поиска всех возможных ходов и запись их в словарь в виде ключа пары (фигура) и вектора пар (ходы)
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			std::vector<std::pair<int, int>> vec; //¬ектор пар возможных ходов дл€ одной фигуры

			if ((i == 0) && (j == 0))
			{
				if ((arr[i][j] == 2) && (arr[i + 1][j] == 0))
				{
					count_player_turn++;

					mapWhite.emplace(std::make_pair(i, j), vec);
					auto it = mapWhite.find(std::make_pair(i, j));
					it->second.push_back(std::make_pair(i + 1, j));
				}
				if ((arr[i][j] == 2) && (arr[i][j + 1] == 0))
				{
					count_player_turn++;

					auto it = mapWhite.find(std::make_pair(i, j));
					if (it != mapWhite.end())
					{
						it->second.push_back(std::make_pair(i, j + 1));
					}
					else
					{
						mapWhite.emplace(std::make_pair(i, j), vec);
						auto it = mapWhite.find(std::make_pair(i, j));
						it->second.push_back(std::make_pair(i, j + 1));
					}
				}

				if ((arr[i][j] == 1) && (arr[i + 1][j] == 0))
				{
					count_AI_turn++;

					mapBlack.emplace(std::make_pair(i, j), vec);
					auto it = mapBlack.find(std::make_pair(i, j));
					it->second.push_back(std::make_pair(i + 1, j));
				}
				if ((arr[i][j] == 1) && (arr[i][j + 1] == 0))
				{
					count_AI_turn++;

					auto it = mapBlack.find(std::make_pair(i, j));

					if (it != mapBlack.end())
					{
						it->second.push_back(std::make_pair(i, j + 1));
					}
					else
					{
						mapBlack.emplace(std::make_pair(i, j), vec);
						auto it = mapBlack.find(std::make_pair(i, j));
						it->second.push_back(std::make_pair(i, j + 1));
					}
				}
			}
			/*else if ((i == SIZE - 1) && (j == SIZE - 1))
			{
				if ((arr[i][j] == 2) && (arr[i - 1][j] == 0))
				{
					count_player_turn++;

					mapWhite.emplace(std::make_pair(i, j), vec);
					auto it = mapWhite.find(std::make_pair(i, j));
					it->second.push_back(std::make_pair(i - 1, j));
				}
				if ((arr[i][j] == 2) && (arr[i][j - 1] == 0))
				{
					count_player_turn++;

					auto it = mapWhite.find(std::make_pair(i, j));

					if (it != mapWhite.end())
					{
						it->second.push_back(std::make_pair(i, j - 1));
					}
					else
					{
						mapWhite.emplace(std::make_pair(i, j), vec);
						auto it = mapWhite.find(std::make_pair(i, j));
						it->second.push_back(std::make_pair(i, j - 1));
					}
				}

				if ((arr[i][j] == 1) && (arr[i - 1][j] == 0))
				{
					count_AI_turn++;

					mapBlack.emplace(std::make_pair(i, j), vec);
					auto it = mapBlack.find(std::make_pair(i, j));
					it->second.push_back(std::make_pair(i - 1, j));
				}
				if ((arr[i][j] == 1) && (arr[i][j - 1] == 0))
				{
					count_AI_turn++;

					auto it = mapBlack.find(std::make_pair(i, j));

					if (it != mapBlack.end())
					{
						it->second.push_back(std::make_pair(i, j - 1));
					}
					else
					{
						mapBlack.emplace(std::make_pair(i, j), vec);
						auto it = mapBlack.find(std::make_pair(i, j));
						it->second.push_back(std::make_pair(i, j - 1));
					}
				}
			}*/
			else if ((i == SIZE - 1) && (j == 0))
			{
				if ((arr[i][j] == 2) && (arr[i - 1][j] == 0))
				{
					count_player_turn++;

					mapWhite.emplace(std::make_pair(i, j), vec);
					auto it = mapWhite.find(std::make_pair(i, j));
					it->second.push_back(std::make_pair(i - 1, j));
				}
				if ((arr[i][j] == 2) && (arr[i][j + 1] == 0))
				{
					count_player_turn++;

					auto it = mapWhite.find(std::make_pair(i, j));

					if (it != mapWhite.end())
					{
						it->second.push_back(std::make_pair(i, j + 1));
					}
					else
					{
						mapWhite.emplace(std::make_pair(i, j), vec);
						auto it = mapWhite.find(std::make_pair(i, j));
						it->second.push_back(std::make_pair(i, j - 1));
					}
				}

				if ((arr[i][j] == 1) && (arr[i - 1][j] == 0))
				{
					count_AI_turn++;

					mapBlack.emplace(std::make_pair(i, j), vec);
					auto it = mapBlack.find(std::make_pair(i, j));
					it->second.push_back(std::make_pair(i - 1, j));
				}
				if ((arr[i][j] == 1) && (arr[i][j + 1] == 0))
				{
					count_AI_turn++;

					auto it = mapBlack.find(std::make_pair(i, j));

					if (it != mapBlack.end())
					{
						it->second.push_back(std::make_pair(i, j + 1));
					}
					else
					{
						mapBlack.emplace(std::make_pair(i, j), vec);
						auto it = mapBlack.find(std::make_pair(i, j));
						it->second.push_back(std::make_pair(i, j + 1));
					}
				}
			}
			else if ((i == 0) && (j == SIZE - 1))
			{
				if ((arr[i][j] == 2) && (arr[i + 1][j] == 0))
				{
					count_player_turn++;

					mapWhite.emplace(std::make_pair(i, j), vec);
					auto it = mapWhite.find(std::make_pair(i, j));
					it->second.push_back(std::make_pair(i + 1, j));
				}
				if ((arr[i][j] == 2) && (arr[i][j - 1] == 0))
				{
					count_player_turn++;

					auto it = mapWhite.find(std::make_pair(i, j));

					if (it != mapWhite.end())
					{
						it->second.push_back(std::make_pair(i, j - 1));
					}
					else
					{
						mapWhite.emplace(std::make_pair(i, j), vec);
						auto it = mapWhite.find(std::make_pair(i, j));
						it->second.push_back(std::make_pair(i, j - 1));
					}
				}

				if ((arr[i][j] == 1) && (arr[i + 1][j] == 0))
				{
					count_AI_turn++;

					mapBlack.emplace(std::make_pair(i, j), vec);
					auto it = mapBlack.find(std::make_pair(i, j));
					it->second.push_back(std::make_pair(i + 1, j));
				}
				if ((arr[i][j] == 1) && (arr[i][j - 1] == 0))
				{
					count_AI_turn++;

					auto it = mapBlack.find(std::make_pair(i, j));

					if (it != mapBlack.end())
					{
						it->second.push_back(std::make_pair(i, j - 1));
					}
					else
					{
						mapBlack.emplace(std::make_pair(i, j), vec);
						auto it = mapBlack.find(std::make_pair(i, j));
						it->second.push_back(std::make_pair(i, j - 1));
					}
				}
			}
			else if (i == 0)
			{
				if ((arr[i][j] == 2) && (arr[i + 1][j] == 0))
				{
					count_player_turn++;

					mapWhite.emplace(std::make_pair(i, j), vec);
					auto it = mapWhite.find(std::make_pair(i, j));
					it->second.push_back(std::make_pair(i + 1, j));
				}
				if ((arr[i][j] == 2) && (arr[i][j + 1] == 0))
				{
					count_player_turn++;

					auto it = mapWhite.find(std::make_pair(i, j));

					if (it != mapWhite.end())
					{
						it->second.push_back(std::make_pair(i, j + 1));
					}
					else
					{
						mapWhite.emplace(std::make_pair(i, j), vec);
						auto it = mapWhite.find(std::make_pair(i, j));
						it->second.push_back(std::make_pair(i, j + 1));
					}
				}
				if ((arr[i][j] == 2) && (arr[i][j - 1] == 0))
				{
					count_player_turn++;

					auto it = mapWhite.find(std::make_pair(i, j));

					if (it != mapWhite.end())
					{
						it->second.push_back(std::make_pair(i, j - 1));
					}
					else
					{
						mapWhite.emplace(std::make_pair(i, j), vec);
						auto it = mapWhite.find(std::make_pair(i, j));
						it->second.push_back(std::make_pair(i, j - 1));
					}
				}

				if ((arr[i][j] == 1) && (arr[i + 1][j] == 0))
				{
					count_AI_turn++;

					mapBlack.emplace(std::make_pair(i, j), vec);
					auto it = mapBlack.find(std::make_pair(i, j));
					it->second.push_back(std::make_pair(i + 1, j));
				}
				if ((arr[i][j] == 1) && (arr[i][j + 1] == 0))
				{
					count_AI_turn++;

					auto it = mapBlack.find(std::make_pair(i, j));

					if (it != mapBlack.end())
					{
						it->second.push_back(std::make_pair(i, j + 1));
					}
					else
					{
						mapBlack.emplace(std::make_pair(i, j), vec);
						auto it = mapBlack.find(std::make_pair(i, j));
						it->second.push_back(std::make_pair(i, j + 1));
					}
				}
				if ((arr[i][j] == 1) && (arr[i][j - 1] == 0))
				{
					count_AI_turn++;

					auto it = mapBlack.find(std::make_pair(i, j));

					if (it != mapBlack.end())
					{
						it->second.push_back(std::make_pair(i, j - 1));
					}
					else
					{
						mapBlack.emplace(std::make_pair(i, j), vec);
						auto it = mapBlack.find(std::make_pair(i, j));
						it->second.push_back(std::make_pair(i, j - 1));
					}
				}
			}
			else if (j == 0)
			{
				if ((arr[i][j] == 2) && (arr[i + 1][j] == 0))
				{
					count_player_turn++;

					mapWhite.emplace(std::make_pair(i, j), vec);
					auto it = mapWhite.find(std::make_pair(i, j));
					it->second.push_back(std::make_pair(i + 1, j));
				}
				if ((arr[i][j] == 2) && (arr[i - 1][j] == 0))
				{
					count_player_turn++;

					auto it = mapWhite.find(std::make_pair(i, j));

					if (it != mapWhite.end())
					{
						it->second.push_back(std::make_pair(i - 1, j));
					}
					else
					{
						mapWhite.emplace(std::make_pair(i, j), vec);
						auto it = mapWhite.find(std::make_pair(i, j));
						it->second.push_back(std::make_pair(i - 1, j));
					}
				}
				if ((arr[i][j] == 2) && (arr[i][j + 1] == 0))
				{
					count_player_turn++;

					auto it = mapWhite.find(std::make_pair(i, j));

					if (it != mapWhite.end())
					{
						it->second.push_back(std::make_pair(i, j + 1));
					}
					else
					{
						mapWhite.emplace(std::make_pair(i, j), vec);
						auto it = mapWhite.find(std::make_pair(i, j));
						it->second.push_back(std::make_pair(i, j + 1));
					}
				}

				if ((arr[i][j] == 1) && (arr[i + 1][j] == 0))
				{
					count_AI_turn++;

					mapBlack.emplace(std::make_pair(i, j), vec);
					auto it = mapBlack.find(std::make_pair(i, j));
					it->second.push_back(std::make_pair(i + 1, j));
				}
				if ((arr[i][j] == 1) && (arr[i - 1][j] == 0))
				{
					count_AI_turn++;

					auto it = mapBlack.find(std::make_pair(i, j));

					if (it != mapBlack.end())
					{
						it->second.push_back(std::make_pair(i - 1, j));
					}
					else
					{
						mapBlack.emplace(std::make_pair(i, j), vec);
						auto it = mapBlack.find(std::make_pair(i, j));
						it->second.push_back(std::make_pair(i - 1, j));
					}
				}
				if ((arr[i][j] == 1) && (arr[i][j + 1] == 0))
				{
					count_AI_turn++;

					auto it = mapBlack.find(std::make_pair(i, j));

					if (it != mapBlack.end())
					{
						it->second.push_back(std::make_pair(i, j + 1));
					}
					else
					{
						mapBlack.emplace(std::make_pair(i, j), vec);
						auto it = mapBlack.find(std::make_pair(i, j));
						it->second.push_back(std::make_pair(i, j + 1));
					}
				}
			}
			else if (i == SIZE - 1)
			{
				if ((arr[i][j] == 2) && (arr[i - 1][j] == 0))
				{
					count_player_turn++;

					mapWhite.emplace(std::make_pair(i, j), vec);
					auto it = mapWhite.find(std::make_pair(i, j));
					it->second.push_back(std::make_pair(i - 1, j));
				}
				if ((arr[i][j] == 2) && (arr[i][j + 1] == 0))
				{
					count_player_turn++;

					auto it = mapWhite.find(std::make_pair(i, j));

					if (it != mapWhite.end())
					{
						it->second.push_back(std::make_pair(i, j + 1));
					}
					else
					{
						mapWhite.emplace(std::make_pair(i, j), vec);
						auto it = mapWhite.find(std::make_pair(i, j));
						it->second.push_back(std::make_pair(i, j + 1));
					}
				}
				if ((arr[i][j] == 2) && (arr[i][j - 1] == 0))
				{
					count_player_turn++;

					auto it = mapWhite.find(std::make_pair(i, j));

					if (it != mapWhite.end())
					{
						it->second.push_back(std::make_pair(i, j - 1));
					}
					else
					{
						mapWhite.emplace(std::make_pair(i, j), vec);
						auto it = mapWhite.find(std::make_pair(i, j));
						it->second.push_back(std::make_pair(i, j - 1));
					}
				}

				if ((arr[i][j] == 1) && (arr[i - 1][j] == 0))
				{
					count_AI_turn++;

					mapBlack.emplace(std::make_pair(i, j), vec);
					auto it = mapBlack.find(std::make_pair(i, j));
					it->second.push_back(std::make_pair(i - 1, j));
				}
				if ((arr[i][j] == 1) && (arr[i][j + 1] == 0))
				{
					count_AI_turn++;

					auto it = mapBlack.find(std::make_pair(i, j));

					if (it != mapBlack.end())
					{
						it->second.push_back(std::make_pair(i, j + 1));
					}
					else
					{
						mapBlack.emplace(std::make_pair(i, j), vec);
						auto it = mapBlack.find(std::make_pair(i, j));
						it->second.push_back(std::make_pair(i, j + 1));
					}
				}
				if ((arr[i][j] == 1) && (arr[i][j - 1] == 0))
				{
					count_AI_turn++;

					auto it = mapBlack.find(std::make_pair(i, j));

					if (it != mapBlack.end())
					{
						it->second.push_back(std::make_pair(i, j - 1));
					}
					else
					{
						mapBlack.emplace(std::make_pair(i, j), vec);
						auto it = mapBlack.find(std::make_pair(i, j));
						it->second.push_back(std::make_pair(i, j - 1));
					}
				}
			}
			else if (j == SIZE - 1)
			{
				if ((arr[i][j] == 2) && (arr[i + 1][j] == 0))
				{
					count_player_turn++;

					mapWhite.emplace(std::make_pair(i, j), vec);
					auto it = mapWhite.find(std::make_pair(i, j));
					it->second.push_back(std::make_pair(i + 1, j));
				}
				if ((arr[i][j] == 2) && (arr[i - 1][j] == 0))
				{
					count_player_turn++;

					auto it = mapWhite.find(std::make_pair(i, j));

					if (it != mapWhite.end())
					{
						it->second.push_back(std::make_pair(i - 1, j));
					}
					else
					{
						mapWhite.emplace(std::make_pair(i, j), vec);
						auto it = mapWhite.find(std::make_pair(i, j));
						it->second.push_back(std::make_pair(i - 1, j));
					}
				}
				if ((arr[i][j] == 2) && (arr[i][j - 1] == 0))
				{
					count_player_turn++;

					auto it = mapWhite.find(std::make_pair(i, j));

					if (it != mapWhite.end())
					{
						it->second.push_back(std::make_pair(i, j - 1));
					}
					else
					{
						mapWhite.emplace(std::make_pair(i, j), vec);
						auto it = mapWhite.find(std::make_pair(i, j));
						it->second.push_back(std::make_pair(i, j - 1));
					}
				}

				if ((arr[i][j] == 1) && (arr[i + 1][j] == 0))
				{
					count_AI_turn++;

					mapBlack.emplace(std::make_pair(i, j), vec);
					auto it = mapBlack.find(std::make_pair(i, j));
					it->second.push_back(std::make_pair(i + 1, j));
				}
				if ((arr[i][j] == 1) && (arr[i - 1][j] == 0))
				{
					count_AI_turn++;

					auto it = mapBlack.find(std::make_pair(i, j));

					if (it != mapBlack.end())
					{
						it->second.push_back(std::make_pair(i - 1, j));
					}
					else
					{
						mapBlack.emplace(std::make_pair(i, j), vec);
						auto it = mapBlack.find(std::make_pair(i, j));
						it->second.push_back(std::make_pair(i - 1, j));
					}
				}
				if ((arr[i][j] == 1) && (arr[i][j - 1] == 0))
				{
					count_AI_turn++;

					auto it = mapBlack.find(std::make_pair(i, j));

					if (it != mapBlack.end())
					{
						it->second.push_back(std::make_pair(i, j - 1));
					}
					else
					{
						mapBlack.emplace(std::make_pair(i, j), vec);
						auto it = mapBlack.find(std::make_pair(i, j));
						it->second.push_back(std::make_pair(i, j - 1));
					}
				}
			}
			else
			{
				if ((arr[i][j] == 2) && (arr[i + 1][j] == 0))
				{
					count_player_turn++;

					mapWhite.emplace(std::make_pair(i, j), vec);
					auto it = mapWhite.find(std::make_pair(i, j));
					it->second.push_back(std::make_pair(i + 1, j));
				}
				if ((arr[i][j] == 2) && (arr[i - 1][j] == 0))
				{
					count_player_turn++;

					auto it = mapWhite.find(std::make_pair(i, j));

					if (it != mapWhite.end())
					{
						it->second.push_back(std::make_pair(i - 1, j));
					}
					else
					{
						mapWhite.emplace(std::make_pair(i, j), vec);
						auto it = mapWhite.find(std::make_pair(i, j));
						it->second.push_back(std::make_pair(i - 1, j));
					}
				}
				if ((arr[i][j] == 2) && (arr[i][j + 1] == 0))
				{
					count_player_turn++;

					auto it = mapWhite.find(std::make_pair(i, j));

					if (it != mapWhite.end())
					{
						it->second.push_back(std::make_pair(i, j + 1));
					}
					else
					{
						mapWhite.emplace(std::make_pair(i, j), vec);
						auto it = mapWhite.find(std::make_pair(i, j));
						it->second.push_back(std::make_pair(i, j + 1));
					}
				}
				if ((arr[i][j] == 2) && (arr[i][j - 1] == 0))
				{
					count_player_turn++;

					auto it = mapWhite.find(std::make_pair(i, j));

					if (it != mapWhite.end())
					{
						it->second.push_back(std::make_pair(i, j - 1));
					}
					else
					{
						mapWhite.emplace(std::make_pair(i, j), vec);
						auto it = mapWhite.find(std::make_pair(i, j));
						it->second.push_back(std::make_pair(i, j - 1));
					}
				}

				if ((arr[i][j] == 1) && (arr[i + 1][j] == 0))
				{
					count_AI_turn++;

					mapBlack.emplace(std::make_pair(i, j), vec);
					auto it = mapBlack.find(std::make_pair(i, j));
					it->second.push_back(std::make_pair(i + 1, j));
				}
				if ((arr[i][j] == 1) && (arr[i - 1][j] == 0))
				{
					count_AI_turn++;

					auto it = mapBlack.find(std::make_pair(i, j));

					if (it != mapBlack.end())
					{
						it->second.push_back(std::make_pair(i - 1, j));
					}
					else
					{
						mapBlack.emplace(std::make_pair(i, j), vec);
						auto it = mapBlack.find(std::make_pair(i, j));
						it->second.push_back(std::make_pair(i - 1, j));
					}
				}
				if ((arr[i][j] == 1) && (arr[i][j + 1] == 0))
				{
					count_AI_turn++;

					auto it = mapBlack.find(std::make_pair(i, j));

					if (it != mapBlack.end())
					{
						it->second.push_back(std::make_pair(i, j + 1));
					}
					else
					{
						mapBlack.emplace(std::make_pair(i, j), vec);
						auto it = mapBlack.find(std::make_pair(i, j));
						it->second.push_back(std::make_pair(i, j + 1));
					}
				}
				if ((arr[i][j] == 1) && (arr[i][j - 1] == 0))
				{
					count_AI_turn++;

					auto it = mapBlack.find(std::make_pair(i, j));

					if (it != mapBlack.end())
					{
						it->second.push_back(std::make_pair(i, j - 1));
					}
					else
					{
						mapBlack.emplace(std::make_pair(i, j), vec);
						auto it = mapBlack.find(std::make_pair(i, j));
						it->second.push_back(std::make_pair(i, j - 1));
					}
				}
			}
		}
	}
	//ѕодсчитали кол-во всех доступных ходов

	analysisDepth--;
	//÷икл проверки всех возможных ходов бота с последующей проверкой всех возможных ходов человека n-раз

	int count_turn_for_win_black = 0;
	int count_turn_for_win_white = 0;

	CalculateWay(arr, count_turn_for_win_black, count_turn_for_win_white);

	std::vector<int> vector_point;

	for (auto& blackFigure : mapBlack)
	{
		for (auto& blackTurn : blackFigure.second)
		{
			int **tempArr;
			tempArr = new int*[SIZE];
			for (int i = 0; i < SIZE; i++) tempArr[i] = new int[SIZE];

			for (int i = 0; i < SIZE; i++) for (int j = 0; j < SIZE; j++) tempArr[i][j] = arr[i][j];

			MoveFuncBlack(tempArr, blackFigure.first.first, blackFigure.first.second, blackTurn.first, blackTurn.second);

			int count_next_turn_for_win_black = 0;
			int count_next_turn_for_win_white = 0;

			CalculateWay(tempArr, count_next_turn_for_win_black, count_next_turn_for_win_white);

			

			if (analysisDepth > 0)
			{
				/*for (auto& whiteFigure : mapWhite)
				{
					for (auto& whiteTurn : whiteFigure.second)
					{
						MoveFuncWhite(tempArr, whiteFigure.first.first, whiteFigure.first.second, whiteTurn.first, whiteTurn.second);

						vector_point.push_back(CalculateBestTurn(tempArr));
					}
				}*/
	
				vector_point.push_back(CalculateBestTurn(tempArr));
			}
			else
			{
				vector_point.push_back(count_next_turn_for_win_black);
			}


			for (int i = 0; i < SIZE; i++) delete[] tempArr[i];
			delete[] tempArr;
		}
	}

	analysisDepth++;

	if (analysisDepth == 2)
	{
		int max_point = *std::max_element(vector_point.begin(), vector_point.end());
		int it1 = 0;
		int it2 = 0;
		for (auto it: vector_point)
		{
			it1++;
			if (it == max_point) break;
		}
		for (auto& blackFigure : mapBlack)
		{
			for (auto& blackTurn : blackFigure.second)
			{
				it2++;
				if (it1==it2)
				{
					from_x = blackFigure.first.first;
					from_y = blackFigure.first.second;
					to_x = blackTurn.first;
					to_y = blackTurn.second;
				}
			}
		}

		return 1;
	}
	else
	{
		if (count_turn_for_win_black > *std::max_element(vector_point.begin(), vector_point.end()))
		{
			return count_turn_for_win_black;
		}
		else
		{
			return *std::max_element(vector_point.begin(), vector_point.end());
		}
	}
}

void AIGame::MoveFuncBlack(Field(&field)[SIZE][SIZE], int from_x, int from_y, int to_x, int to_y)
{
	field[from_x][from_y].isBusyBlack = false;
	field[from_x][from_y].isFree = true;
	field[to_x][to_y].isBusyBlack = true;
	field[to_x][to_y].isFree = false;
}

void AIGame::MoveFuncWhite(Field(&field)[SIZE][SIZE], int from_x, int from_y, int to_x, int to_y)
{
	field[from_x][from_y].isBusyWhite = false;
	field[from_x][from_y].isFree = true;
	field[to_x][to_y].isBusyWhite = true;
	field[to_x][to_y].isFree = false;
}

void AIGame::MoveFuncBlack(int** arr, int from_x, int from_y, int to_x, int to_y)
{
	arr[from_x][from_y] = 0;
	arr[to_x][to_y] = 1;
}

void AIGame::MoveFuncWhite(int** arr, int from_x, int from_y, int to_x, int to_y)
{
	arr[from_x][from_y] = 0;
	arr[to_x][to_y] = 2;
}

void AIGame::CalculateWay(int** arr, int& count_turn_to_win_black, int& count_turn_to_win_white)
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (arr[i][j] == 1)
			{
				count_turn_to_win_black += point_black_arr[i][j];
			}
		}
	}
}

