#pragma once

#include "../WildResourceSim/BaseWorld.h"

namespace Model
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	//public class Tile
	//{
	//public:
	//	int x, y;
	//	int cIndex;
	//	Tile(int r, int c, int colorIndex)
	//	{
	//		x = r;
	//		y = c;
	//		cIndex = colorIndex;
	//	}
	//};

	public ref class TileBox : PictureBox
	{
	public:
		static array<Color>^ randColor = { Color::Salmon, Color::Red, Color::Orange, Color::Blue, Color::Navy };
		Tile* tile;
		TileBox(Tile& t, int size, EventHandler^ mouseOverDel) : PictureBox()
		{
			tile = new Tile(t);

			Nature::Biome* b = NULL;
			int bCount = 0;
			tile->GetAllBiomes(b, bCount);
			if (b[0].type == Nature::Wasteland)
				bCount = 0;
			BackColor = randColor[bCount];
			Width = size;
			Height = size;
			this->MouseEnter += mouseOverDel;
		}
	};
}