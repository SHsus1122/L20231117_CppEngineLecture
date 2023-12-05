#include "Player.h"
#include <iostream>
#include <windows.h>
#include "World.h"
#include "SimpleEngine.h"
#include "Goal.h"
#include "GameState.h"

APlayer::APlayer()
{
	Shape = 'P';
	X = 10;
	Y = 10;
	SortOrder = 500;
}

APlayer::APlayer(int NewX, int NewY, char NewShape, int NewSortOrder, SDL_Color NewColor, int NowDirection)
{
	Shape = 'P';
	SetX(NewX);
	SetY(NewY);
	SortOrder = NewSortOrder;
	Color = NewColor;
	LoadBMP("TileData/Player.bmp", SDL_Color { 255, 0, 255, 0 });
	bIsSprite = true;
	SpriteSizeX = 5;
	SpriteSizeY = 5;
	Direction = NowDirection;
}

APlayer::~APlayer()
{
}

void APlayer::Tick()
{
	//AActor::Tick(KeyCode);	// 부모의 것을 호출합니다. 이것이 정규 문법입니다.
	__super::Tick();	// 이것도 동일하나 비주얼 스튜디오(MS) 한정입니다.
	//int KeyCode = SimpleEngine::KeyCode;
	int KeyCode = GEngine->MyEvent.key.keysym.sym;
	
	// 키 입력이 있을때만 가라는 의미
	if (GEngine->MyEvent.type == SDL_KEYDOWN)
	{
		return;
	}

	if (SimpleEngine::GetGameState()->IsGameOver)
	{
		return;
	}

	// 우리는 충돌 관련은 빼고.. 움직임만... 아래처럼 상하좌우 움직임을 구현하게 됩니다.
	// 이제 이를 움직임은 컴포넌트에서 하기 때문에 추후에 컴포넌트 로직으로 변경하게 될 겁니다.
	if (KeyCode == SDLK_a)
	{
		if (!IsCollide(X - 1, Y))
		{
			Direction = 0;
			X--;
		}
	}
	if (KeyCode == SDLK_d)
	{
		if (!IsCollide(X + 1, Y))
		{
			Direction = 1;
			X++;
		}
	}
	if (KeyCode == SDLK_w)
	{
		if (!IsCollide(X, Y - 1))
		{
			Direction = 2;
			Y--;
		}
	}
	if (KeyCode == SDLK_s)
	{
		if (!IsCollide(X, Y + 1))
		{
			Direction = 3;
			Y++;
		}
	}
	if (KeyCode == SDLK_ESCAPE)
	{
		GEngine->Stop();
	}

	AGoal* MyGoal = nullptr;
	for (auto Actor : GEngine->GetWorld()->GetAllActors())
	{
		MyGoal = dynamic_cast<AGoal*>(Actor);
		if (MyGoal &&
			MyGoal->GetX() == X &&
			MyGoal->GetY() == Y)
		{
			// 플레이어가 골을 했다는 것을 의미하며 이를 알려주기만 하고 처리는 다른 곳에서 행하게 됩니다.
			SimpleEngine::GetGameState()->IsNextLevel = true;
			break;
		}
	}
}

bool APlayer::IsCollide	(int NewX, int NewY)
{
	for (const auto& Actor : GEngine->GetWorld()->GetAllActors())
	{
		if (this == Actor)
		{
			continue;
		}
		if (Actor->bCollide == true &&
			Actor->GetX() == NewX &&
			Actor->GetY() == NewY)
		{
			return true;
		}
	}
	return false;
}
