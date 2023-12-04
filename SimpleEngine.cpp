#include "SimpleEngine.h"
#include "World.h"
#include <conio.h>	// _getch �Է°� �ޱ� ���ؼ� ��Ŭ���
#include "Player.h"
#include <iostream>
#include "Wall.h"
#include "Monster.h"
#include "Floor.h"
#include "Goal.h"
#include "GameMode.h"
#include "GameState.h"

#include <iostream>
#include <fstream>

SimpleEngine* SimpleEngine::Instance = nullptr;
int SimpleEngine::KeyCode = 0;

SimpleEngine::SimpleEngine()
{
	GameMode = nullptr;
	GameState = nullptr;
	SDL_Init(SDL_INIT_EVERYTHING);
	MyWindow = SDL_CreateWindow("HelloWorld", 100, 100, 800, 600, SDL_WINDOW_OPENGL);

	MyRenderer = SDL_CreateRenderer(MyWindow, -1, SDL_RENDERER_ACCELERATED
		| SDL_RENDERER_PRESENTVSYNC
		| SDL_RENDERER_TARGETTEXTURE);

	Init();
}

SimpleEngine::~SimpleEngine()
{
	Term();
	SDL_DestroyRenderer(MyRenderer);
	SDL_DestroyWindow(MyWindow);
	SDL_Quit();
}

void SimpleEngine::Init()
{
	IsRunning = true;
	World = new UWorld();	// ���� ����
}

void SimpleEngine::Run()
{
	while (IsRunning)
	{
		// �� �����ӿ� �ɸ� �ð� �������� ���ؼ�
		DeltaSeconds = SDL_GetTicks64() - LastTime;
		LastTime = SDL_GetTicks64();
		Input();
		// �̺�Ʈ ó�� �κ�
		switch (MyEvent.type)
		{
			// ���⼭ ���� �ݱ� ��ư���� �ϰڴٴ� �ǹ�
		case SDL_QUIT:
			IsRunning = false;
			break;
		case SDL_KEYDOWN:
			// SDL_KEYDOWN �� Ű �Է� �̺�Ʈ��, SDLK_ESCAPE �� ESC Ű�� ������ �����ϴ�.
			if (MyEvent.key.keysym.sym == SDLK_ESCAPE)
			{
				IsRunning = false;
			}
			break;
		}
		// �۾� ���� �� �����
		// Input
		// Tick
		// Render
		// World; // ��� ���ư��� �ؼ�
		// ������ ���� ó���� �ϸ� �� ���� �մϴ�. ���� ȭ�鵵 �����ϴ� ��... �츮�� �ʿ� �����ϴ�.
		//Input();
		Tick();
		// �����ϱ� ���� �� ������ ȭ�� ����� Clear Screen
		//system("cls");	// �� �ڵ尡 ȭ�� ����� �ڵ��Դϴ�.


		SDL_SetRenderDrawColor(GEngine->MyRenderer, 0, 0, 0, 0);
		SDL_RenderClear(GEngine->MyRenderer);

		Render();

		SDL_RenderPresent(GEngine->MyRenderer);
	}
}

void SimpleEngine::Stop()
{
	IsRunning = false;
}

void SimpleEngine::Term()
{
	GameMode = nullptr;
	GameState = nullptr;
	IsRunning = false;
	delete World;
}

void SimpleEngine::LoadLevel(std::string Filename)
{
	// ���͵��� ��ġ�ϸ鼭 ���͵��� �ε� ���ֵ��� �մϴ�.
	// Memory -> Disk : Serialize, Text(Json, csv), binary(umap)
	// �޸𸮿� �ִ� ���� ��ũ�� �����ϱ����� �ø�������� �ϴ� �۾�
	//GetWorld()->SpawnActor(new APlayer(10, 10));
	//
	// �� �ؿ��� �ٴ��� �־�� �մϴ�.
	// �츮 �ڵ忡���� ���µ� ������ �ٴڵ� �����ؾ� �մϴ�.
	//std::string Map[10] = {
	//	"**********",
	//	"*P       *",
	//	"*     M  *",
	//	"*        *",
	//	"*        *",
	//	"*        *",
	//	"*        *",
	//	"* M      *",
	//	"*       G*",
	//	"**********",
	//};

	int Y = 0;
	std::string line;
	std::ifstream file(Filename);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			for (int X = 0; X < line.length(); ++X)
			{
				LoadActor(X, Y, line[X]);
			}
			Y++;
		}
		file.close();
	}
	else
	{
		Stop();
	}

	GetWorld()->SortRenderOrder();

	// ���� ���Ӹ�带 ������ �����ϰ� �մϴ�.
	GameMode = new AGameMode();
	GetWorld()->SpawnActor(GameMode);
	GameState = new AGameState();
	GetWorld()->SpawnActor(GameState);


	/*for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (i == 0 || i == 9 || j == 0 || j == 9)
			{
				GetWorld()->SpawnActor(new AWall(j, i));
			}
		}
	}*/

	// Disk -> Memory : Deserialize 
	// �� �ݴ밡 �Ǵ� �۾��� ����Դϴ�. Deserialize ��� �մϴ�.
}

// Ű �Է� ������ Ű �� ����
void SimpleEngine::Input()
{
	SDL_PollEvent(&MyEvent);
	//KeyCode = MyEvent.key.keysym.sym;
}

// ƽ���� �ϴ� ���� ��� ���Ϳ� ���� ó��
// ���Ϳ��� Ű�� �༭ �װ��� ������ �Է¿� �°� �������� �ϱ� �����Դϴ�.
void SimpleEngine::Tick()
{
	GetWorld()->Tick();
}

void SimpleEngine::Render()
{
	GetWorld()->Render();
}

void SimpleEngine::LoadActor(int NewX, int NewY, char Actor)
{
	if (Actor == '*')
	{
		// Wall
		GetWorld()->SpawnActor(new AWall(NewX, NewY));
	}
	else if (Actor == 'P')
	{
		// Player
		GetWorld()->SpawnActor(new APlayer(NewX, NewY));
	}
	else if (Actor == 'M')
	{
		// Monster
		GetWorld()->SpawnActor(new AMonster(NewX, NewY));
	}
	else if (Actor == 'G')
	{
		// Goal
		GetWorld()->SpawnActor(new AGoal(NewX, NewY));
	}
	else if (Actor == ' ')
	{
		// Floor
	}
	// Floor
	GetWorld()->SpawnActor(new AFloor(NewX, NewY));
}
