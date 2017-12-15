// SphereOfInfluanceTesting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

const int ROW = 100;
const int COL = 100;
int matrix[ROW][COL];

//*
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
}
//*/

void drawcircle(int x0, int y0, int radius);
void putpixel(int x, int y);
int main()
{
	initmatrix();
	for (int i = 0; i < 6; i++)
	{
		int radius;
		std::cout << "Input a radius: ";
		std::cin >> radius;

		int x = std::rand() % ROW;
		int y = std::rand() % COL;

		for (; radius > 1; radius--)
		{
			//drawcircle(ROW / 2, COL / 2, radius);
			drawcircle(x, y, radius);
		}
	}
	printmatrix();
	std::cout << std::endl;

	return 0;
}

void putpixel(int x, int y)
{
	if (x < 0 || y < 0 || x >= ROW || y >= COL)
		return;

	matrix[x][y]++;
	printf("(%2d,%2d),", x, y);
}

void drawcircle(int x0, int y0, int radius)
{
	int x = radius - 1;
	int y = 0;
	int dx = 1;
	int dy = 1;
	int err = dx - (radius << 1);

	while (x >= y)
	{
		putpixel(x0 + x, y0 + y);
		putpixel(x0 + y, y0 + x);
		putpixel(x0 - y, y0 + x);
		putpixel(x0 - x, y0 + y);
		putpixel(x0 - x, y0 - y);
		putpixel(x0 - y, y0 - x);
		putpixel(x0 + y, y0 - x);
		putpixel(x0 + x, y0 - y);
		printf("\n");

		if (err <= 0)
		{
			y++;
			err += dy;
			dy += 2;
		}
		if (err > 0)
		{
			x--;
			dx += 2;
			err += dx - (radius << 1);
		}
	}
}