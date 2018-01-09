#pragma once

#include <cstdio>
#include "TileBox.h"

namespace WorldCLIQuickViewer {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    const int size = 20;
    const int bourder = 3;
    const int bufferRadius = 25;
    const int w = 500;
    const int h = 500;
    /// <summary>
    /// Summary for QuickViewer
    /// </summary>
    public ref class QuickViewer : public System::Windows::Forms::Form
    {
    private:
        bool f_dragging = false;
        System::Drawing::Point mouseDown;
    private:
        System::Windows::Forms::GroupBox^ tileGroup;
        Tile* displayedTile;

    public:
        QuickViewer(void)
        {
            float 
                forst1Mag = 40, forst2Mag = 30, 
                water1Mag = 50, 
                plains1Mag = 40, plains2Mag = 10, 
                quarry1Mag = 60, 
                mount1Mag = 20
                ;

            world = new World::BaseWorld(w, h);
            world->SetBiome(5, 5, 3, Nature::Forest, forst1Mag);
            world->SetBiome(4, 4, 3, Nature::Water, water1Mag);
            world->SetBiome(3, 7, 2, Nature::Forest, forst2Mag);
            world->SetBiome(4, 6, 1, Nature::Plains, plains1Mag);
            world->SetBiome(9, 3, 4, Nature::Plains, plains2Mag);
            world->SetBiome(10, 10, 4, Nature::Quarry, quarry1Mag);
            world->SetBiome(12, 12, 6, Nature::Mountains, mount1Mag);
            world->FinalizeWorld();

            InitializeComponent();

            System::Windows::Forms::MouseEventHandler^ EH_tBox_mouseMoved = gcnew System::Windows::Forms::MouseEventHandler(this, &QuickViewer::tileBox_MouseMove);
            System::Windows::Forms::MouseEventHandler^ EH_tBox_mouseDown = gcnew System::Windows::Forms::MouseEventHandler(this, &QuickViewer::tileBox_MouseDown);
            System::Windows::Forms::MouseEventHandler^ EH_tBox_mouseUp = gcnew System::Windows::Forms::MouseEventHandler(this, &QuickViewer::tileBox_MouseUp);
            tileGroup = gcnew GroupBox();

            tileGroup->MouseMove += EH_tBox_mouseMoved;
            tileGroup->MouseDown += EH_tBox_mouseDown;
            tileGroup->MouseUp += EH_tBox_mouseUp;

            World::BaseWorld::TileCache* cache = world->BuildCache(10, 10, bufferRadius);
            while (!cache->empty())
            {
                World::TileReference t = cache->top();
                Model::TileBox^ tBox = InitializeTileBox(t);
                tileGroup->Controls->Add(tBox);
                cache->pop();
            }

            //for (int c = 0; c < w; c++)
            //{
            //    for (int r = 0; r < h; r++)
            //    {
            //        Model::TileBox^ tBox = InitializeTileBox(r, c);
            //        tileGroup->Controls->Add(tBox);
            //    }
            //}
            tileGroup->AutoSize = true;
            groupBox_pre->Controls->Add(tileGroup);
        }

    protected:
        void setTile(Tile* tile)
        {
            displayedTile = tile;
            label_x->Text = tile->x.ToString();
            label_y->Text = tile->y.ToString();

            label_biomes->Text = "";
            Nature::Biome* biomes;
            int bCount;
            tile->GetAllBiomes(biomes, bCount);
            for (int i = 0; i < bCount; i++)
                label_biomes->Text += ((int)biomes[i].type).ToString() + ": " + RoundForDisplay(biomes[i].magnitude).ToString() + "\n";

            Nature::Resources res = tile->AvailableResources();
            label_resources->Text = "";
            label_resources->Text += "Cattle:   " + res.cattle + "\n";
            label_resources->Text += "Crops:    " + res.crops + "\n";
            label_resources->Text += "Stone:    " + res.stone + "\n";
            label_resources->Text += "Terrain:  " + res.terrain + "\n";
            label_resources->Text += "Water:    " + res.water + "\n";
            label_resources->Text += "Wildlife: " + res.wildlife + "\n";
            label_resources->Text += "Wood:     " + res.wood + "\n";
        }

        Model::TileBox^ InitializeTileBox(World::TileReference tile)
        {
            return InitializeTileBox(tile.x, tile.y);
        }

        Model::TileBox^ InitializeTileBox(int x, int y)
        {
            System::EventHandler^ EH_tBox_mouseEnter = gcnew EventHandler(this, &QuickViewer::tileBox_mouseEnter);
            MouseEventHandler^ EH_tBox_mouseMoved = gcnew MouseEventHandler(this, &QuickViewer::tileBox_MouseMove);
            MouseEventHandler^ EH_tBox_mouseDown = gcnew MouseEventHandler(this, &QuickViewer::tileBox_MouseDown);
            MouseEventHandler^ EH_tBox_mouseUp = gcnew MouseEventHandler(this, &QuickViewer::tileBox_MouseUp);

            Tile* tile = world->GetGridTile(x, y);
            Model::TileBox^ tBox = gcnew Model::TileBox(*tile, size, EH_tBox_mouseEnter);
            tBox->Left = bourder + x * (size + bourder);
            tBox->Top = bourder + y * (size + bourder);
            tBox->MouseMove += EH_tBox_mouseMoved;
            tBox->MouseDown += EH_tBox_mouseDown;
            tBox->MouseUp += EH_tBox_mouseUp;

            return tBox;
        }

        double RoundForDisplay(double value)
        {
            return round(value * 1000.0) / 1000.0;
        }

        void TickWorld()
        {
            static int p = 0;
            world->Tick();
            label_iterations->Text = (++p).ToString();

            for (int i = 0; i < this->Controls->Count; i++)
            {
                Model::TileBox^ tBox = dynamic_cast<Model::TileBox^>(this->Controls[i]);
                if (tBox)
                    tBox->CalcuateColor();
            }
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
    private: System::Windows::Forms::GroupBox^  groupBox_pre;



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
            this->groupBox_pre = (gcnew System::Windows::Forms::GroupBox());
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
            // groupBox_pre
            // 
            this->groupBox_pre->Location = System::Drawing::Point(110, 9);
            this->groupBox_pre->Name = L"groupBox_pre";
            this->groupBox_pre->Size = System::Drawing::Size(390, 448);
            this->groupBox_pre->TabIndex = 20;
            this->groupBox_pre->TabStop = false;
            this->groupBox_pre->Text = L"World Preview";
            // 
            // QuickViewer
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(512, 469);
            this->Controls->Add(this->groupBox_pre);
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
    private: System::Void tileBox_mouseEnter(System::Object^  sender, System::EventArgs^  e)
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
    private: System::Void tileBox_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
    {
        // Reference Shamelessly copied: https://social.msdn.microsoft.com/Forums/vstudio/en-US/5823e285-6999-40f5-b28a-74480a0acb13/proper-way-to-zoom-and-pan-images?forum=csharpgeneral
        bool dragging = e->Button == System::Windows::Forms::MouseButtons::Left;
        if (dragging)
        {
            Model::TileBox^ tBox = dynamic_cast<Model::TileBox^>(sender);
            System::Object^ group = (tBox == nullptr) ? sender : tBox->Parent;
            System::Windows::Forms::Control^ control = dynamic_cast<Control^>(group);
            if (control != nullptr)
            {
                Point mousePosNow = e->Location;

                int deltaX = mousePosNow.X - mouseDown.X;
                int deltaY = mousePosNow.Y - mouseDown.Y;

                int newX = control->Location.X + deltaX;
                int newY = control->Location.Y + deltaY;

                control->Location = Point(newX, newY);
            }
        }
    }
    private: System::Void tileBox_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
    {
        if (e->Button == System::Windows::Forms::MouseButtons::Left)
        {
            mouseDown = e->Location;
        }
    }
    private: System::Void tileBox_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
    {
        if (e->Button == System::Windows::Forms::MouseButtons::Left && displayedTile != NULL)
        {
            tileGroup->Enabled = false;
            tileGroup->Visible = false;
            tileGroup->Controls->Clear();

            World::BaseWorld::TileCache* cache = world->BuildCache(displayedTile->x, displayedTile->y, bufferRadius);
            while (!cache->empty())
            {
                World::TileReference t = cache->top();
                Model::TileBox^ tBox = InitializeTileBox(t);
                tileGroup->Controls->Add(tBox);
                cache->pop();
            }
            tileGroup->Visible = true;
            tileGroup->Enabled = true;
        }
    }
};
}
