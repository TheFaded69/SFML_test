#pragma once
#include "Field.h"
#include <cmath>
//#include "Multilist.h"

class AIGame
{
private:
	int** arr; //????????? ?????? ??? ???????? ?????? ?? ???? ??? ????

	int point_black_arr[8][8]{ {0, 93, 172, 237, 288, 348, 357},
							 {93,192,277,348,405,448,477,492},
	                         {172,277,368,445,508,557,592,613},
	                         {237,348,445,528,597,652,693,710},
	                         {288,405,508,597,672,733,750,800},
	                         {325,448,557,652,733,825,858,912},
	                         {348,477,592,693,750,858,912,962},
	                         {357,492,613,710,800,912,962,1008} };

	/*int point_white_arr[8][8]{{10,9,8,3,3,3,2,1},
							   {9,8,7,3,3,2,1,1},
							   {8,7,6,3,2,1,1,0},
							   {3,3,3,2,1,1,0,0},
							   {3,3,2,1,1,0,0,0},
							   {3,2,1,1,0,0,0,0},
							   {2,1,1,0,0,0,0,-3},
							   {1,1,0,0,0,0,-3,-5} };*/


	int from_x;
	int from_y;
	int to_x;
	int to_y;

	int analysisDepth = 2;	

	//Multilist<std::pair<int, std::pair<std::pair<int,int>, std::pair<int,int>>>> list;  //??????? ??????, ??? ???????? ??? ??????? ????? ?????

public:
	AIGame();
	~AIGame();
	void UpdateArr(Field(&field)[SIZE][SIZE]);
	void DoTurn(Field (&field)[SIZE][SIZE]);
	void SearchBestTurn(Field(&field)[SIZE][SIZE]);

	int turn_count = 0;
	
	int CalculateShortestPath(int from_x, int from_y, int to_x, int to_y) { return abs(to_x + to_y - from_x - from_y); }
	int CalculateBestTurn(int** arr);
	void MoveFuncBlack(Field(&field)[SIZE][SIZE], int from_x, int from_y, int to_x, int to_y); //????? ??? ?????? ????
	void MoveFuncWhite(Field(&field)[SIZE][SIZE], int from_x, int from_y, int to_x, int to_y);
	void MoveFuncBlack(int** arr, int from_x, int from_y, int to_x, int to_y);   //????? ??? ???????? ??????? ???? ? ?????? ???????
	void MoveFuncWhite(int** arr, int from_x, int from_y, int to_x, int to_y);
	void CalculateWay(int** arr, int& count_turn_to_win_black, int& count_turn_to_win_white);
};



