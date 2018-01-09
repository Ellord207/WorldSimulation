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
		static array<Color>^ PalletColor = 
        { 
            Color::DarkGray,
            Color::DarkGreen, 
            Color::Goldenrod, 
            Color::LightGreen, 
            Color::Navy,
            Color::Orange,
            Color::RosyBrown,
            Color::SkyBlue
        };
		Tile* tile;
		TileBox(Tile& t, int size, EventHandler^ mouseOverDel) : PictureBox()
		{
            tile = &t;
            CalcuateColor();
			Width = size;
			Height = size;
			this->MouseEnter += mouseOverDel;
		}

        /// <summary>Blends the specified colors together.</summary>
        /// <param name="color">Color to blend onto the background color.</param>
        /// <param name="backColor">Color to blend the other color onto.</param>
        /// <param name="amount">How much of <paramref name="color"/> to keep,
        /// “on top of” <paramref name="backColor"/>.</param>
        /// <returns>The blended colors.</returns>
        static Color Blend(Color color, Color backColor, double amount)
        {
            int r = (int)((color.R * amount) + backColor.R * (1 - amount));
            int g = (int)((color.G * amount) + backColor.G * (1 - amount));
            int b = (int)((color.B * amount) + backColor.B * (1 - amount));
            return Drawing::Color::FromArgb(r, g, b);
        }
        void CalcuateColor()
        {
            
            Nature::Biome* b = NULL;
            int bCount = 0;
            tile->GetAllBiomes(b, bCount);
            
            Color color = PalletColor[(int)b[0].type];

            for (int i = 1; i < bCount; i++)
            {
                Color newColor = PalletColor[(int)b[i].type];
                color = Blend(newColor, color, b[i].magnitude / 100);
            }
            BackColor = color;
        }
	};
}