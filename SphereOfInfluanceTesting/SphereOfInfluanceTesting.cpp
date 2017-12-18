// SphereOfInfluanceTesting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include "CustomMatrix.h"
#include <time.h>

void drawcircle(int x0, int y0, int radius);
void fillcircle1(int x0, int y0, int radius);
void fillcircle2(int x0, int y0, int radius);

double TimeAlgorithm(void (algorithm)(int, int, int), int x, int y, int radius);

int main()
{

	int radius;
	std::cout << "Input a radius: ";
	std::cin >> radius;

	int x = ROW/2;//std::rand() % ROW;
	int y = COL/2;//std::rand() % COL;

	initmatrix();
	std::cout << "algorithm 1" << std::setprecision(5) << TimeAlgorithm(fillcircle1, x, y, radius) << "[ms]" << std::endl;
	//drawcircle(x, y, radius);
	//std::cout << "algorithm 2" << std::setprecision(5) << TimeAlgorithm(fillcircle2, x, y, radius) << "[ms]" << std::endl;
	printmatrix();

	return 0;
}

double TimeAlgorithm(void (func)(int, int, int), int x, int y, int radius)
{
	clock_t start = clock();

	func(x, y, radius);

	clock_t end = clock();
	double time = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
	return time;
}

//**************************************************//
//				 THE CHOSEN ALORGITHM				//
//**************************************************//
void fillcircle1(int x0, int y0, int radius)
{
	int r = radius;
	for (int x1 = x0 - r + 1; x1 < x0 + r; x1++)
	{
		for (int y1 = y0 - r + 1; y1 < y0 + r; y1++)
		{
			int dx = x0 - x1; // horizontal offset
			int dy = y0 - y1; // vertical offset
			if ((dx*dx + dy*dy) <= (r*r))
			{
				putpixel(x1, y1);
			}
		}
	}
}
//**************************************************//
//**************************************************//

void fillcircle2(int x0, int y0, int radius)
{
	for (; radius > 1; radius--)
		drawcircle(x0, y0, radius);
}

void inline drawcircle(int x0, int y0, int radius)
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