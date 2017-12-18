#pragma once

#include <iostream>
#include <string>

const int ROW = 100;
const int COL = 100;
int matrix[ROW][COL];

void printmatrix();
void initmatrix();
void putpixel(int x, int y);


void initmatrix()
{
	for (size_t row = 0; row < ROW; row++)
	{
		for (size_t col = 0; col < COL; col++)
		{
			matrix[row][col] = 0;
		}
	}
}
void printmatrix()
{
	for (size_t row = 0; row < ROW; row++)
	{
		for (size_t col = 0; col < COL; col++)
		{
			std::cout << "|" << matrix[row][col];
		}
		std::cout << "|" << std::endl;
	}
	std::string s;
	//std::cin >> s;
	std::cout << std::endl;
}
inline void putpixel(int x, int y)
{
	if (x < 0 || y < 0 || x >= ROW || y >= COL)
		return;

	matrix[x][y]++;
	//printf("(%2d,%2d),", x, y);
}

