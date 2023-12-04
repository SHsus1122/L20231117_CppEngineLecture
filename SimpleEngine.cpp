#include "SimpleEngine.h"
#include "World.h"
#include <conio.h>	// _getch 입력값 받기 위해서 인클루드
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
	World = new UWorld();	// 월드 생성
}

void SimpleEngine::Run()
{
	while (IsRunning)
	{
		// 한 프레임에 걸린 시간 가져오기 위해서
		DeltaSeconds = SDL_GetTicks64() - LastTime;
		LastTime = SDL_GetTicks64();
		Input();
		// 이벤트 처리 부분
		switch (MyEvent.type)
		{
			// 여기서 이제 닫기 버튼만을 하겠다는 의미
		case SDL_QUIT:
			IsRunning = false;
			break;
		case SDL_KEYDOWN:
			// SDL_KEYDOWN 는 키 입력 이벤트며, SDLK_ESCAPE 는 ESC 키를 누르면 꺼집니다.
			if (MyEvent.key.keysym.sym == SDLK_ESCAPE)
			{
				IsRunning = false;
			}
			break;
		}
		// 작업 순서 및 내용들
		// Input
		// Tick
		// Render
		// World; // 계속 돌아가야 해서
		// 원래는 물리 처리도 하면 더 좋긴 합니다. 이후 화면도 복구하는 등... 우리는 필요 없습니다.
		//Input();
		Tick();
		// 랜더하기 전에 할 일으로 화면 지우기 Clear Screen
		//system("cls");	// 이 코드가 화면 지우기 코드입니다.


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
	// 액터들을 배치하면서 액터들을 로딩 해주도록 합니다.
	// Memory -> Disk : Serialize, Text(Json, csv), binary(umap)
	// 메모리에 있는 것을 디스크에 저장하기위해 시리얼라이즈 하는 작업
	//GetWorld()->SpawnActor(new APlayer(10, 10));
	//
	// 벽 밑에는 바닥이 있어야 합니다.
	// 우리 코드에서는 없는데 원래는 바닥도 존재해야 합니다.
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

	// 이제 게임모드를 강제로 구현하게 합니다.
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
	// 그 반대가 되는 작업을 방법입니다. Deserialize 라고 합니다.
}

// 키 입력 받으면 키 값 리턴
void SimpleEngine::Input()
{
	SDL_PollEvent(&MyEvent);
	//KeyCode = MyEvent.key.keysym.sym;
}

// 틱에서 하는 것은 모든 액터에 대한 처리
// 액터에게 키를 줘서 그것이 맞으면 입력에 맞게 움직여야 하기 때문입니다.
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
