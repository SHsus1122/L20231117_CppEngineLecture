#include "SimpleEngine.h"
#include "World.h"
#include <conio.h>	// _getch 입력값 받기 위해서 인클루드
#include "Player.h"
#include <iostream>
#include "Wall.h"
#include "Monster.h"
#include "Floor.h"
#include "Goal.h"

SimpleEngine* SimpleEngine::Instance = nullptr;

SimpleEngine::SimpleEngine()
{
	Init();
}

SimpleEngine::~SimpleEngine()
{	
	Term();
}

void SimpleEngine::Init()
{
	IsRunning = true;
	World = new UWorld();	// 월드 생성
}

void SimpleEngine::Run()
{
	while (IsRunning)
	{
		// 작업 순서 및 내용들
		// Input
		// Tick
		// Render
		// World; // 계속 돌아가야 해서
		int KeyCode = Input();

		// 원래는 물리 처리도 하면 더 좋긴 합니다. 이후 화면도 복구하는 등... 우리는 필요 없습니다.
		Tick(KeyCode);
		// 랜더하기 전에 할 일으로 화면 지우기 Clear Screen
		system("cls");	// 이 코드가 화면 지우기 코드입니다.
		Render();
	}
}

void SimpleEngine::Stop()
{
	IsRunning = false;
}

void SimpleEngine::Term()
{
	IsRunning = false;
	delete World;
}

void SimpleEngine::LoadLevel(std::string Filename)
{
	// 액터들을 배치하면서 액터들을 로딩 해주도록 합니다.
	// Memory -> Disk : Serialize, Text(Json, csv), binary(umap)
	// 메모리에 있는 것을 디스크에 저장하기위해 시리얼라이즈 하는 작업
	//GetWorld()->SpawnActor(new APlayer(10, 10));
	
	// 벽 밑에는 바닥이 있어야 합니다.
	// 우리 코드에서는 없는데 원래는 바닥도 존재해야 합니다.
	std::string Map[10] = {
		"**********",
		"*P       *",
		"*        *",
		"*        *",
		"*    M   *",
		"*        *",
		"*        *",
		"*        *",
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
	// 그 반대가 되는 작업을 방법입니다. Deserialize 라고 합니다.
}

// 키 입력 받으면 키 값 리턴
int SimpleEngine::Input()
{
	int KeyCode = _getch();

	return KeyCode;
}

// 틱에서 하는 것은 모든 액터에 대한 처리
// 액터에게 키를 줘서 그것이 맞으면 입력에 맞게 움직여야 하기 때문입니다.
void SimpleEngine::Tick(int KeyCode)
{
	GetWorld()->Tick(KeyCode);
}

void SimpleEngine::Render()
{
	GetWorld()->Render();
}
