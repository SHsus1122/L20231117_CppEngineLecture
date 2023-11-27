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

SimpleEngine* SimpleEngine::Instance = nullptr;
int SimpleEngine::KeyCode = 0;

SimpleEngine::SimpleEngine()
{
	GameMode = nullptr;
	GameState = nullptr;
	Init();
}

SimpleEngine::~SimpleEngine()
{	
	Term();
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
		// �۾� ���� �� �����
		// Input
		// Tick
		// Render
		// World; // ��� ���ư��� �ؼ�
		// ������ ���� ó���� �ϸ� �� ���� �մϴ�. ���� ȭ�鵵 �����ϴ� ��... �츮�� �ʿ� �����ϴ�.
		Input();
		Tick();
		// �����ϱ� ���� �� ������ ȭ�� ����� Clear Screen
		system("cls");	// �� �ڵ尡 ȭ�� ����� �ڵ��Դϴ�.
		Render();
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
	
	// �� �ؿ��� �ٴ��� �־�� �մϴ�.
	// �츮 �ڵ忡���� ���µ� ������ �ٴڵ� �����ؾ� �մϴ�.
	std::string Map[10] = {
		"**********",
		"*P       *",
		"*     M  *",
		"*        *",
		"*        *",
		"*        *",
		"*        *",
		"* M      *",
		"*       G*",
		"**********",
	};

	for (int X = 0; X < 10; X++)
	{
		for (int Y = 0; Y < 10; Y++)
		{
			if (Map[Y][X] == '*')
			{
				// Wall
				GetWorld()->SpawnActor(new AWall(X, Y));
			}
			else if (Map[Y][X] == 'P')
			{
				// Player
				GetWorld()->SpawnActor(new APlayer(X, Y));
			}
			else if (Map[Y][X] == 'M')
			{
				// Monster
				GetWorld()->SpawnActor(new AMonster(X, Y));
			}
			else if (Map[Y][X] == 'G')
			{
				// Goal
				GetWorld()->SpawnActor(new AGoal(X, Y));
			}
			else if (Map[Y][X] == ' ')
			{
				// Floor
			}
			// Floor
			GetWorld()->SpawnActor(new AFloor(X, Y));
		}
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
	KeyCode = _getch();
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
