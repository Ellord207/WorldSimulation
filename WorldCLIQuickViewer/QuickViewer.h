#pragma once

#include "TileBox.h"

namespace WorldCLIQuickViewer {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	const int size = 20;
	const int bourder = 5;
	const int offset = 100;
	const int w = 15;
	const int h = 15;
	/// <summary>
	/// Summary for QuickViewer
	/// </summary>
	public ref class QuickViewer : public System::Windows::Forms::Form
	{
	public:
		QuickViewer(void)
		{
			float forst1Mag = 40, forst2Mag = 30, water1Mag = 50, plains1Mag = 40;
			world = new World::BaseWorld(w, h);
			world->SetBiome(5, 5, 2, Nature::Forest, forst1Mag);
			world->SetBiome(4, 4, 3, Nature::Water, water1Mag);
			world->SetBiome(3, 7, 2, Nature::Forest, forst2Mag);
			world->SetBiome(4, 6, 1, Nature::Plains, plains1Mag);
			world->FinalizeWorld();

			InitializeComponent();
			Random^ rnd = gcnew Random();
			System::EventHandler^ eh = gcnew EventHandler(this, &QuickViewer::MouseEnter);

			for (int c = 0; c < w; c++)
			{
				for (int r = 0; r < h; r++)
				{
					Tile* tile = world->GetGridTile(r, c);
					Model::TileBox^ tBox = gcnew Model::TileBox(*tile, size, eh);
					tBox->Left = offset + r * (size + bourder);
					tBox->Top = bourder + c * (size + bourder);
					this->Controls->Add(tBox);
				}
			}
		}

	protected:
		void setTile(Tile* tile)
		{
			label_x->Text = tile->x.ToString();
			label_y->Text = tile->y.ToString();
			
			label_biomes->Text = "";
			Nature::Biome* biomes;
			int bCount;
			tile->GetAllBiomes(biomes, bCount);
			for (int i = 0; i < bCount; i++)
				label_biomes->Text += ((int)biomes[i].type).ToString() + ": " + biomes[i].magnitude.ToString() + "\n";

			Nature::Resources res = tile->AvailableResources();
			label_resources->Text = "";
			label_resources->Text += "Cattle:   " + res.cattle + "\n";
			label_resources->Text += "Crops:    " + res.crops + "\n";
			label_resources->Text += "stone:    " + res.stone + "\n";
			label_resources->Text += "Terrain:  " + res.terrain + "\n";
			label_resources->Text += "Water:    " + res.water + "\n";
			label_resources->Text += "Wildlife: " + res.wildlife + "\n";
			label_resources->Text += "Wood:     " + res.wood + "\n";

		}

		void TickWorld()
		{
			static int p = 0;

			bool b = world->IsBiome(3, 7, Nature::BiomeType::Wasteland);
			World::BaseWorld::TileCache* cache = world->BuildCache(h/2, w/2, std::max(h,w));
			int size = cache->size();
			while (!cache->empty())
			{
				World::TileReference t = cache->top();
				cache->pop();	
			}
			world->Tick();
			label_iterations->Text = (++p).ToString();
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~QuickViewer()
		{
			if (components)
			{
				delete components;
			}
			world->~BaseWorld();
		}
	protected:
	private: World::BaseWorld* world = NULL;
	private: System::Windows::Forms::Label^  label_y;
	private: System::Windows::Forms::Label^  label_x;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label_biomes;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label_resources;
	private: System::Windows::Forms::Button^  butt_tickSingle;
	private: System::Windows::Forms::Button^  butt_tickTen;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label_iterations;



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label_y = (gcnew System::Windows::Forms::Label());
			this->label_x = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label_biomes = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label_resources = (gcnew System::Windows::Forms::Label());
			this->butt_tickSingle = (gcnew System::Windows::Forms::Button());
			this->butt_tickTen = (gcnew System::Windows::Forms::Button());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label_iterations = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label_y
			// 
			this->label_y->AutoSize = true;
			this->label_y->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_y->Location = System::Drawing::Point(44, 34);
			this->label_y->Name = L"label_y";
			this->label_y->Size = System::Drawing::Size(59, 20);
			this->label_y->TabIndex = 11;
			this->label_y->Text = L"00000";
			// 
			// label_x
			// 
			this->label_x->AutoSize = true;
			this->label_x->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_x->Location = System::Drawing::Point(44, 9);
			this->label_x->Name = L"label_x";
			this->label_x->Size = System::Drawing::Size(59, 20);
			this->label_x->TabIndex = 10;
			this->label_x->Text = L"00000";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(12, 34);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(26, 20);
			this->label2->TabIndex = 9;
			this->label2->Text = L"Y:";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(26, 20);
			this->label1->TabIndex = 8;
			this->label1->Text = L"X:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(16, 58);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(41, 13);
			this->label3->TabIndex = 12;
			this->label3->Text = L"Biomes";
			// 
			// label_biomes
			// 
			this->label_biomes->AutoSize = true;
			this->label_biomes->Location = System::Drawing::Point(16, 75);
			this->label_biomes->Name = L"label_biomes";
			this->label_biomes->Size = System::Drawing::Size(37, 13);
			this->label_biomes->TabIndex = 13;
			this->label_biomes->Text = L"_____";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(16, 198);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(58, 13);
			this->label4->TabIndex = 14;
			this->label4->Text = L"Resources";
			// 
			// label_resources
			// 
			this->label_resources->AutoSize = true;
			this->label_resources->Location = System::Drawing::Point(16, 211);
			this->label_resources->Name = L"label_resources";
			this->label_resources->Size = System::Drawing::Size(37, 13);
			this->label_resources->TabIndex = 15;
			this->label_resources->Text = L"_____";
			// 
			// butt_tickSingle
			// 
			this->butt_tickSingle->Location = System::Drawing::Point(13, 434);
			this->butt_tickSingle->Name = L"butt_tickSingle";
			this->butt_tickSingle->Size = System::Drawing::Size(75, 23);
			this->butt_tickSingle->TabIndex = 16;
			this->butt_tickSingle->Text = L"Single Tick";
			this->butt_tickSingle->UseVisualStyleBackColor = true;
			this->butt_tickSingle->Click += gcnew System::EventHandler(this, &QuickViewer::butt_tickSingle_Click);
			// 
			// butt_tickTen
			// 
			this->butt_tickTen->Location = System::Drawing::Point(13, 405);
			this->butt_tickTen->Name = L"butt_tickTen";
			this->butt_tickTen->Size = System::Drawing::Size(75, 23);
			this->butt_tickTen->TabIndex = 17;
			this->butt_tickTen->Text = L"Ten Ticks";
			this->butt_tickTen->UseVisualStyleBackColor = true;
			this->butt_tickTen->Click += gcnew System::EventHandler(this, &QuickViewer::butt_tickTen_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(10, 389);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(53, 13);
			this->label5->TabIndex = 18;
			this->label5->Text = L"Iterations:";
			// 
			// label_iterations
			// 
			this->label_iterations->AutoSize = true;
			this->label_iterations->Location = System::Drawing::Point(70, 389);
			this->label_iterations->Name = L"label_iterations";
			this->label_iterations->Size = System::Drawing::Size(13, 13);
			this->label_iterations->TabIndex = 19;
			this->label_iterations->Text = L"0";
			// 
			// QuickViewer
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(512, 469);
			this->Controls->Add(this->label_iterations);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->butt_tickTen);
			this->Controls->Add(this->butt_tickSingle);
			this->Controls->Add(this->label_resources);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label_biomes);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label_y);
			this->Controls->Add(this->label_x);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Name = L"QuickViewer";
			this->Text = L"QuickViewer";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MouseEnter(System::Object^  sender, System::EventArgs^  e)
	{
		Model::TileBox^ tBox = dynamic_cast<Model::TileBox^>(sender);
		if (tBox != nullptr)
			setTile(tBox->tile);
	}
	private: System::Void butt_tickSingle_Click(System::Object^  sender, System::EventArgs^  e)
	{
		TickWorld();
	}
	private: System::Void butt_tickTen_Click(System::Object^  sender, System::EventArgs^  e)
	{
		for (int i = 0; i < 10; i++)
			TickWorld();
	}
};
}
