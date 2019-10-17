/*
Project Name: IN628 2019 Assignment 1: 2D Roguelike
Student Name: Hua(Aemooooon) WANG
Lecturer Name: Grayson, Nathan
*/

// MyForm Class is main application UI entry.
// Its hold all controllers and Instans of Game Objects
// Also all status check instead of Game Manager class

#pragma once
#include "TileMap.h"
#include "Tile.h"
#include "Room.h"
#include "Dungeon.h"
#include "Viewport.h"
#include "SpriteList.h"
#include "KnightSprite.h"

// Define all constant
#define NCOLS 120 // World map cols
#define NROWS 90 // World map rows
#define MOVESPEED 8 // Player Speed
#define NROOMS 8 // Romms Number
#define HEALTH 100 // Player healty by default

// All Window Size below
#define FORMWIDTH 960
#define FORMHEIGHT 640
#define VIEWWHDTH 356
#define VIEWHEIGHT 240
#define FORCEWIDTH 400
#define FORCEHEIGHT 300

// define viewport args
#define TILEWIDTH 32
#define VIEWPORTTILESWIDE 30
#define VIEWPORTTILESHEIGHT 20

namespace Roguelike {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Timer^  timer1;
	protected:
	private: System::ComponentModel::IContainer^  components;

	private:
		///////////////////////////////////////////////////////////////////////////////////////////////
		// All Objects and instances define
		///////////////////////////////////////////////////////////////////////////////////////////////
		Random^ rGen;
		Graphics^ mainCanvas;
		TileMap^ mainTileMap;
		Dungeon^ mainDungeon;
		Viewport^ mainViewport;

		TileMap^ blackTileMap;
		TileSet^ blackTileSet;

		Bitmap^ backgroundImage;
		Bitmap^ offScreenBitmap;
		Graphics^ offScreenCanvas;

		SpriteList^ wizardSpriteList;
		SpriteList^ yellowSpriteList;
		SpriteList^ fountainSpriteList;

		Sprite^ effect;
		Sprite^ effectA;
		Sprite^ effectB;
		Sprite^ knight;

		int x;
		int y;
		int powerScore = HEALTH;
		int score = 0;

		bool isKeyDown = false;

		List<Room^>^ rooms;

	/// <summary>
	/// Required designer variable.
	/// </summary>
	private: System::Windows::Forms::ProgressBar^  pPower; //Player heathy status
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::PictureBox^  pictureBox2;

	private: System::Windows::Forms::Label^  lblScore;


#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// Required method for Designer support - do not modify
			 /// the contents of this method with the code editor.
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 this->components = (gcnew System::ComponentModel::Container());
				 System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
				 this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
				 this->lblScore = (gcnew System::Windows::Forms::Label());
				 this->pPower = (gcnew System::Windows::Forms::ProgressBar());
				 this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
				 this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
				 this->SuspendLayout();
				 // 
				 // timer1
				 // 
				 this->timer1->Interval = 37;
				 this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
				 // 
				 // lblScore
				 // 
				 this->lblScore->AutoSize = true;
				 this->lblScore->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
					 static_cast<System::Int32>(static_cast<System::Byte>(0)));
				 this->lblScore->Location = System::Drawing::Point(395, 270);
				 this->lblScore->Name = L"lblScore";
				 this->lblScore->Size = System::Drawing::Size(0, 13);
				 this->lblScore->TabIndex = 0;
				 // 
				 // pPower
				 // 
				 this->pPower->ForeColor = System::Drawing::Color::Red;
				 this->pPower->Location = System::Drawing::Point(370, 260);
				 this->pPower->Margin = System::Windows::Forms::Padding(0);
				 this->pPower->Name = L"pPower";
				 this->pPower->Size = System::Drawing::Size(100, 8);
				 this->pPower->Step = 1;
				 this->pPower->Style = System::Windows::Forms::ProgressBarStyle::Continuous;
				 this->pPower->TabIndex = 2;
				 this->pPower->Value = 1;
				 // 
				 // pictureBox1
				 // 
				 this->pictureBox1->Cursor = System::Windows::Forms::Cursors::Hand;
				 this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
				 this->pictureBox1->Location = System::Drawing::Point(370, 250);
				 this->pictureBox1->Name = L"pictureBox1";
				 this->pictureBox1->Size = System::Drawing::Size(127, 127);
				 this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
				 this->pictureBox1->TabIndex = 3;
				 this->pictureBox1->TabStop = false;
				 this->pictureBox1->Click += gcnew System::EventHandler(this, &MyForm::pictureBox1_Click);
				 // 
				 // pictureBox2
				 // 
				 this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.Image")));
				 this->pictureBox2->Location = System::Drawing::Point(180, 26);
				 this->pictureBox2->Name = L"pictureBox2";
				 this->pictureBox2->Size = System::Drawing::Size(600, 218);
				 this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
				 this->pictureBox2->TabIndex = 4;
				 this->pictureBox2->TabStop = false;
				 // 
				 // MyForm
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(960, 640);
				 this->Controls->Add(this->pictureBox2);
				 this->Controls->Add(this->pictureBox1);
				 this->Controls->Add(this->pPower);
				 this->Controls->Add(this->lblScore);
				 this->Name = L"MyForm";
				 this->Text = L"Aemooooon RogueLike Game";
				 this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
				 this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
				 this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
				 this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyUp);
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }
#pragma endregion
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
		///////////////////////////////////////////////////////////////////////////////////////////////
		// All Objects and instances initialization
		///////////////////////////////////////////////////////////////////////////////////////////////
		rGen = gcnew Random();
		mainCanvas = CreateGraphics();

		// Doube bullfer
		offScreenBitmap = gcnew Bitmap(FORMWIDTH, FORMHEIGHT);
		offScreenCanvas = Graphics::FromImage(offScreenBitmap);
		backgroundImage = gcnew Bitmap(FORMWIDTH, FORMHEIGHT);

		// Define tiles
		Bitmap^ startTileBitmap1 = gcnew Bitmap("Cobblestones Tile 32.bmp");
		Bitmap^ startTileBitmap2 = gcnew Bitmap("Dry Grass Tile 32.bmp");
		Bitmap^ startTileBitmap3 = gcnew Bitmap("Flower Tile 32.bmp");

		Bitmap^ bg_black = gcnew Bitmap("black.bmp");
		//Color transparentColor = bg_black->GetPixel(0, 0);
		//bg_black->MakeTransparent(transparentColor);

		Tile^ tileToEnter1 = gcnew Tile(startTileBitmap1, true);
		Tile^ tileToEnter2 = gcnew Tile(startTileBitmap2, false);
		Tile^ tileToEnter3 = gcnew Tile(startTileBitmap3, false);
		Tile^ tileToEnter4 = gcnew Tile(bg_black, false);

		// real tileset which puts all real tiles number
		TileSet^ tileList = gcnew TileSet(4);
		tileList->SetTileArrayEntry(0, tileToEnter1);
		tileList->SetTileArrayEntry(1, tileToEnter2);
		tileList->SetTileArrayEntry(2, tileToEnter3);
		tileList->SetTileArrayEntry(3, tileToEnter4);

		// all tiles black just make fog default
		TileSet^ blackTileSet = gcnew TileSet(4);
		blackTileSet->SetTileArrayEntry(0, tileToEnter4);
		blackTileSet->SetTileArrayEntry(1, tileToEnter4);
		blackTileSet->SetTileArrayEntry(2, tileToEnter4);
		blackTileSet->SetTileArrayEntry(3, tileToEnter4);


		mainTileMap = gcnew TileMap(tileList, mainCanvas, NCOLS, NROWS);
		blackTileMap= gcnew TileMap(blackTileSet, mainCanvas, NCOLS, NROWS);

		mainDungeon = gcnew Dungeon(mainTileMap, NCOLS, NROWS, 3, NROOMS, rGen);

		// make rooms
		mainDungeon->ClearDungeon();
		mainDungeon->MakeNewDungeon(); // Fill map structure
		x = mainDungeon->GetRndRoomXY()->X * TILEWIDTH;
		y = mainDungeon->GetRndRoomXY()->Y * TILEWIDTH;
		rooms = mainDungeon->GetRooms();

		//generater game objects
		knight = generateKnightSprite();

		wizardSpriteList = gcnew SpriteList();
		generateWizardSprite();

		yellowSpriteList = gcnew SpriteList();
		generateYellowSprite();


		fountainSpriteList = gcnew SpriteList();
		generateFountainSprite();

		effect = generateEffectSprite();
		effectA = generateEffectASprite();
		effectB = generateEffectBSprite();

		// draw view port 
		mainViewport = gcnew Viewport(x - FORCEWIDTH, y - FORCEHEIGHT, VIEWPORTTILESWIDE, VIEWPORTTILESHEIGHT, TILEWIDTH, NCOLS, NROWS, mainTileMap, offScreenCanvas);

		//timer1->Enabled = true;

	}

	private: System::Void MyForm_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		//mainTileMap->DrawMap();
		//mainViewport->ViewportDraw();
	}

	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
		offScreenCanvas->DrawImage(backgroundImage, Rectangle(0, 0, FORMWIDTH, FORMHEIGHT));

		//mainDungeon->ClearDungeon();
		mainViewport->FogOfWar(mainTileMap, knight->XPos,knight->YPos);
		
		mainViewport->ViewportDraw(blackTileMap);

		

		knight->ForcedDraw(FORCEWIDTH, FORCEHEIGHT);
		knight->UpdateFrame();

		// Default effect around the Player
		if (!isKeyDown)
		{
			effect->ForcedDraw(VIEWWHDTH,VIEWHEIGHT);
			effect->UpdateFrame();
			effect->Move(mainTileMap);
		}

		// Calculate the yellow object hurt Player Health
		if (yellowSpriteList->CheckCollisionsWithBoss(knight))
		{
			powerScore -= 1;
		}

		lblScore->Text = "Score: "+score.ToString();

		// Calculate the Health of Player when entry Power of Fountaion
		if (fountainSpriteList->Intersection(knight))
		{
			if (powerScore < HEALTH)
			{
				powerScore += 1;
			}

		}

		// Check Player heath status
		if (powerScore == 0)
		{
			timer1->Enabled = false;
			MessageBox::Show("Game Over...");
		}

		if (score>=200)
		{
			timer1->Enabled = false;
			MessageBox::Show("You Win...");
		}

		if (powerScore <= HEALTH && powerScore >= 0)
		{
			pPower->Value = powerScore;
		}

		// draw game object and effects
		fountainSpriteList->DrawSpritesInViewport(mainViewport->ViewportWorldX, mainViewport->ViewportWorldY, FORMWIDTH, FORMHEIGHT);
		fountainSpriteList->UpdateFrame();
		fountainSpriteList->WanderSprites(mainTileMap, knight);

		wizardSpriteList->DrawSpritesInViewport(mainViewport->ViewportWorldX, mainViewport->ViewportWorldY, FORMWIDTH, FORMHEIGHT);
		wizardSpriteList->UpdateFrame();
		wizardSpriteList->WanderSprites(mainTileMap);

		yellowSpriteList->DrawSpritesInViewport(mainViewport->ViewportWorldX, mainViewport->ViewportWorldY, FORMWIDTH, FORMHEIGHT);
		yellowSpriteList->UpdateFrame();
		yellowSpriteList->WanderSprites(mainTileMap, knight);

		mainCanvas->DrawImage(offScreenBitmap, 0, 0);
	}

	private: System::Void MyForm_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {

		mainViewport->moveRelativeToPlayer(knight->XPos, knight->YPos);

		mainViewport->FogOfWar(mainTileMap,knight->XPos, knight->YPos);
		mainViewport->ViewportDraw(blackTileMap);

		// set whether KeyDown flag
		isKeyDown = true;

		switch (e->KeyData)
		{
		case Keys::Left:
		case Keys::A:
			knight->SpriteDirection = EDirection::WEST; // change direction
			runEffect();                                // Play effect
			break;
		case Keys::Up:
		case Keys::W:
			knight->SpriteDirection = EDirection::NORTH;
			runEffect();
			break;
		case Keys::Down:
		case Keys::S:
			knight->SpriteDirection = EDirection::SOUTH;
			runEffect();
			break;
		case Keys::Right:
		case Keys::D:
			knight->SpriteDirection = EDirection::EAST;
			runEffect();
			break;
		case Keys::Space:
			knight->SpriteDirection = EDirection::EAST;

			effectB->UpdateFrame();
			effectB->ForcedDraw(VIEWWHDTH, VIEWHEIGHT);

			knight->UpdateFrame();
			knight->ForcedDraw(FORCEWIDTH, FORCEHEIGHT);

			wizardSpriteList->DrawSpritesInViewport(mainViewport->ViewportWorldX, mainViewport->ViewportWorldY, FORMWIDTH, FORMHEIGHT);
			wizardSpriteList->UpdateFrame();
			wizardSpriteList->WanderSprites(mainTileMap);

			yellowSpriteList->DrawSpritesInViewport(mainViewport->ViewportWorldX, mainViewport->ViewportWorldY, FORMWIDTH, FORMHEIGHT);
			yellowSpriteList->UpdateFrame();
			yellowSpriteList->WanderSprites(mainTileMap, knight);


			fountainSpriteList->DrawSpritesInViewport(mainViewport->ViewportWorldX, mainViewport->ViewportWorldY, FORMWIDTH, FORMHEIGHT);
			fountainSpriteList->UpdateFrame();
			fountainSpriteList->WanderSprites(mainTileMap);

			// check collision between Player and Yellow Objects
			if (yellowSpriteList->Intersection(knight))
			{
				yellowSpriteList->CheckCollisions(knight);
				score += 4;
			}

			// check collision between Player and Wizard Objects
			if (wizardSpriteList->Intersection(knight))
			{
				wizardSpriteList->CheckCollisions(knight);
				if (powerScore < HEALTH && powerScore >= 0)
				{
					powerScore++;
				}
				score++;
			}

			break;
		}

		mainCanvas->DrawImage(offScreenBitmap, 0, 0);
	}

	private: System::Void MyForm_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		isKeyDown = false;
	}

	// Method encapuslate the Game objects Drawing and UpdateFrame
	private: void runEffect()
	{
		knight->Move(mainTileMap);
		knight->UpdateFrame();
		knight->ForcedDraw(FORCEWIDTH, FORCEHEIGHT);

		effectA->ForcedDraw(VIEWWHDTH, VIEWHEIGHT);
		effectA->UpdateFrame();
		effectA->Move(mainTileMap);

		wizardSpriteList->DrawSpritesInViewport(mainViewport->ViewportWorldX, mainViewport->ViewportWorldY, FORMWIDTH, FORMHEIGHT);
		wizardSpriteList->UpdateFrame();
		wizardSpriteList->WanderSprites(mainTileMap);

		yellowSpriteList->DrawSpritesInViewport(mainViewport->ViewportWorldX, mainViewport->ViewportWorldY, FORMWIDTH, FORMHEIGHT);
		yellowSpriteList->UpdateFrame();
		yellowSpriteList->WanderSprites(mainTileMap, knight);


		fountainSpriteList->DrawSpritesInViewport(mainViewport->ViewportWorldX, mainViewport->ViewportWorldY, FORMWIDTH, FORMHEIGHT);
		fountainSpriteList->UpdateFrame();
		fountainSpriteList->WanderSprites(mainTileMap);
	}

	// make Player object
	private: Sprite^ generateKnightSprite()
	{
		int framesInKnightSpriteSheet = 8;
		int directions = 4;

		Bitmap^ east = gcnew Bitmap("Knight Walk East 8.bmp");
		Bitmap^ south = gcnew Bitmap("Knight Walk South 8.bmp");
		Bitmap^ west = gcnew Bitmap("Knight Walk West 8.bmp");
		Bitmap^ north = gcnew Bitmap("Knight Walk North 8.bmp");

		array<Bitmap^>^ knightImages = gcnew array<Bitmap^>(directions);
		knightImages[EDirection::EAST] = east;
		knightImages[EDirection::SOUTH] = south;
		knightImages[EDirection::WEST] = west;
		knightImages[EDirection::NORTH] = north;

		for (int d = 0; d < directions; d++)
		{
			Color transparentColor = knightImages[d]->GetPixel(0, 0);
			knightImages[d]->MakeTransparent(transparentColor);
		}

		Sprite^ kSprite = gcnew KnightSprite(offScreenCanvas, knightImages, framesInKnightSpriteSheet, rGen);
		kSprite->XVel = MOVESPEED;
		kSprite->YVel = MOVESPEED;
		kSprite->XPos = x;
		kSprite->YPos = y;

		return kSprite;
	}

	// make Wizrad objects
	private: void generateWizardSprite()
	{
		int framesInWizardSpriteSheet = 8;
		int directions = 4;

		Bitmap^ east = gcnew Bitmap("Wizard.bmp");
		Bitmap^ south = gcnew Bitmap("Wizard.bmp");
		Bitmap^ west = gcnew Bitmap("Wizard.bmp");
		Bitmap^ north = gcnew Bitmap("Wizard.bmp");

		array<Bitmap^>^ wizardImages = gcnew array<Bitmap^>(directions);
		wizardImages[EDirection::EAST] = east;
		wizardImages[EDirection::SOUTH] = south;
		wizardImages[EDirection::WEST] = west;
		wizardImages[EDirection::NORTH] = north;

		for (int d = 0; d < directions; d++)
		{
			Color transparentColor = wizardImages[d]->GetPixel(0, 0);
			wizardImages[d]->MakeTransparent(transparentColor);
		}

		for (int i = 0; i < 100; i++)
		{
			Sprite^ newSprite = gcnew Sprite(offScreenCanvas, wizardImages, framesInWizardSpriteSheet, rGen);
			int flip = rGen->Next(rooms->Count);
			int flip_x;
			int flip_y;
			for (int i = 0; i < rooms->Count; i++)
			{
				flip_x = rGen->Next(rooms[flip]->X1 * 32 + 32, rooms[flip]->X2 * 32 - 64);
				flip_y = rGen->Next(rooms[flip]->Y1 * 32 + 32, rooms[flip]->Y2 * 32 - 64);
			}
			newSprite->XPos = flip_x;
			newSprite->YPos = flip_y;

			newSprite->XVel = 1;
			newSprite->YVel = 1;
			wizardSpriteList->AddSprite(newSprite);
		}

	}

    // make Default effect of Player objects
	private: Sprite^ generateEffectSprite()
	{
		int framesInEffectSpriteSheet = 6;
		int directions = 4;

		Bitmap^ east = gcnew Bitmap("effect.png");
		Bitmap^ south = gcnew Bitmap("effect.png");
		Bitmap^ west = gcnew Bitmap("effect.png");
		Bitmap^ north = gcnew Bitmap("effect.png");

		array<Bitmap^>^ knightImages = gcnew array<Bitmap^>(directions);
		knightImages[EDirection::EAST] = east;
		knightImages[EDirection::SOUTH] = south;
		knightImages[EDirection::WEST] = west;
		knightImages[EDirection::NORTH] = north;

		for (int d = 0; d < directions; d++)
		{
			Color transparentColor = knightImages[d]->GetPixel(0, 0);
			knightImages[d]->MakeTransparent(transparentColor);
		}

		Sprite^ eSprite = gcnew Sprite(offScreenCanvas, knightImages, framesInEffectSpriteSheet, rGen);
		eSprite->XVel = 0;
		eSprite->YVel = 0;
		eSprite->XPos = knight->XPos - 40;
		eSprite->YPos = knight->YPos - 48;

		return eSprite;

	}

	// make effect A objects
	private: Sprite^ generateEffectASprite()
	{
		int framesInEffectSpriteSheet = 6;
		int directions = 4;

		Bitmap^ east = gcnew Bitmap("effect01.png");
		Bitmap^ south = gcnew Bitmap("effect01.png");
		Bitmap^ west = gcnew Bitmap("effect01.png");
		Bitmap^ north = gcnew Bitmap("effect01.png");

		array<Bitmap^>^ knightImages = gcnew array<Bitmap^>(directions);
		knightImages[EDirection::EAST] = east;
		knightImages[EDirection::SOUTH] = south;
		knightImages[EDirection::WEST] = west;
		knightImages[EDirection::NORTH] = north;

		for (int d = 0; d < directions; d++)
		{
			Color transparentColor = knightImages[d]->GetPixel(0, 0);
			knightImages[d]->MakeTransparent(transparentColor);
		}

		Sprite^ eSprite = gcnew Sprite(offScreenCanvas, knightImages, framesInEffectSpriteSheet, rGen);
		eSprite->XVel = 0;
		eSprite->YVel = 0;
		eSprite->XPos = knight->XPos - 40;
		eSprite->YPos = knight->YPos - 48;

		return eSprite;

	}

	// make effect B object
	private: Sprite^ generateEffectBSprite()
	{
		int framesInEffectSpriteSheet = 12;
		int directions = 4;

		Bitmap^ east = gcnew Bitmap("effect04.png");
		Bitmap^ south = gcnew Bitmap("effect04.png");
		Bitmap^ west = gcnew Bitmap("effect04.png");
		Bitmap^ north = gcnew Bitmap("effect04.png");

		array<Bitmap^>^ knightImages = gcnew array<Bitmap^>(directions);
		knightImages[EDirection::EAST] = east;
		knightImages[EDirection::SOUTH] = south;
		knightImages[EDirection::WEST] = west;
		knightImages[EDirection::NORTH] = north;

		for (int d = 0; d < directions; d++)
		{
			Color transparentColor = knightImages[d]->GetPixel(0, 0);
			knightImages[d]->MakeTransparent(transparentColor);
		}

		Sprite^ eSprite = gcnew Sprite(offScreenCanvas, knightImages, framesInEffectSpriteSheet, rGen);
		eSprite->XVel = 0;
		eSprite->YVel = 0;
		eSprite->XPos = knight->XPos - 40;
		eSprite->YPos = knight->YPos - 48;

		return eSprite;

	}

	// make Yellow objects
	private: void generateYellowSprite()
	{
		int framesInWizardSpriteSheet = 40;
		int directions = 4;

		Bitmap^ east = gcnew Bitmap("yellowShip.bmp");
		Bitmap^ south = gcnew Bitmap("yellowShip.bmp");
		Bitmap^ west = gcnew Bitmap("yellowShip.bmp");
		Bitmap^ north = gcnew Bitmap("yellowShip.bmp");

		array<Bitmap^>^ wizardImages = gcnew array<Bitmap^>(directions);
		wizardImages[EDirection::EAST] = east;
		wizardImages[EDirection::SOUTH] = south;
		wizardImages[EDirection::WEST] = west;
		wizardImages[EDirection::NORTH] = north;

		for (int d = 0; d < directions; d++)
		{
			Color transparentColor = wizardImages[d]->GetPixel(0, 0);
			wizardImages[d]->MakeTransparent(transparentColor);
		}

		for (int i = 0; i <= 24; i++)
		{
			Sprite^ newSprite = gcnew Sprite(offScreenCanvas, wizardImages, framesInWizardSpriteSheet, rGen);
			int flip = rGen->Next(rooms->Count);
			int flip_x;
			int flip_y;
			for (int i = 0; i < rooms->Count; i++)
			{
				flip_x = rooms[flip]->Centre_X * 32;
				flip_y = rooms[flip]->Centre_Y * 32;
			}
			newSprite->XPos = flip_x;
			newSprite->YPos = flip_y;

			newSprite->XVel = 1;
			newSprite->YVel = 1;
			yellowSpriteList->AddSprite(newSprite);
		}

	}

	// make Power of Fountain
	private: void generateFountainSprite()
	{
		int framesInWizardSpriteSheet = 12;
		int directions = 4;

		Bitmap^ east = gcnew Bitmap("effect02.png");
		Bitmap^ south = gcnew Bitmap("effect02.png");
		Bitmap^ west = gcnew Bitmap("effect02.png");
		Bitmap^ north = gcnew Bitmap("effect02.png");

		array<Bitmap^>^ wizardImages = gcnew array<Bitmap^>(directions);
		wizardImages[EDirection::EAST] = east;
		wizardImages[EDirection::SOUTH] = south;
		wizardImages[EDirection::WEST] = west;
		wizardImages[EDirection::NORTH] = north;

		for (int d = 0; d < directions; d++)
		{
			Color transparentColor = wizardImages[d]->GetPixel(0, 0);
			wizardImages[d]->MakeTransparent(transparentColor);
		}

		for (int i = 0; i < NROOMS; i++)
		{
			Sprite^ newSprite = gcnew Sprite(offScreenCanvas, wizardImages, framesInWizardSpriteSheet, rGen);
			int flip = rGen->Next(rooms->Count);
			int flip_x;
			int flip_y;
			for (int i = 0; i < rooms->Count; i++)
			{
				flip_x = rooms[flip]->Centre_X * 32 - 64;
				flip_y = rooms[flip]->Centre_Y * 32 - 64;
			}
			newSprite->XPos = flip_x;
			newSprite->YPos = flip_y;

			newSprite->XVel = 1;
			newSprite->YVel = 1;
			fountainSpriteList->AddSprite(newSprite);
		}

	}

	private: System::Void pictureBox1_Click(System::Object^  sender, System::EventArgs^  e) {
		timer1->Enabled = true;
		pictureBox1->Visible = false;
		pictureBox2->Visible = false;
	}
};
}
