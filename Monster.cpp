#include "Monster.h"
#include "Windows.h"
#include "SimpleEngine.h"
#include "World.h"
#include "player.h"
#include <iostream>
#include <random>
#include "GameState.h"

AMonster::AMonster()
{
	Shape = 'M';
	X = 10;
	Y = 10;
	SortOrder = 300;
	bCollide = false;
	srand((unsigned int)time(nullptr));
}

AMonster::AMonster(int NewX, int NewY, char NewShape, int NewSortOrder)
{
	Shape = NewShape;
	SetX(NewX);
	SetY(NewY);
	SortOrder = NewSortOrder;
}

AMonster::~AMonster()
{
}

void AMonster::Tick()
{
	__super::Tick();
	//int KeyCode = SimpleEngine::KeyCode;
	
	//std::random_device rd;
	//std::mt19937_64 rng(rd());
	//std::uniform_int_distribution<__int64> dist1(0, 3);
	/*std::random_device rd;
	std::mt19937_64 rng(rd());

	std::uniform_int_distribution<__int64> dist1(1, 4);

	switch (dist1(rng))
	{
	case 1:
		if (!IsCollide(X - 1, Y))
		{
			X--;
		}
		break;
	case 2:
		if (!IsCollide(X + 1, Y))
		{
			X++;
		}
		break;
	case 3:
		if (!IsCollide(X, Y - 1))
		{
			Y--;
		}
		break;
	default:
		if (!IsCollide(X, Y + 1))
		{
			Y++;
		}
		break;
	}*/

	// 플레이어 충돌 확인
	for (const auto& Actor : GEngine->GetWorld()->GetAllActors())
	{
		// 모든 액터로부터 찾아온 정보로부터 플레이어 위치와 몬스터가 같으면...!
		APlayer* MyPlayer = dynamic_cast<APlayer*>(Actor);
		if (MyPlayer &&
			MyPlayer->GetX() == X &&
			MyPlayer->GetY() == Y)
		{
			// 몬스터가 플레이어를 죽였다는 것을 알려주기만 하고 처리는 다른곳에서 행합니다.
			// ::GetGameState()->IsGameOver = true;
			SimpleEngine::GetGameState()->IsGameOver = true;
			return;
		}
	}

	int Direction = rand() % 4;
	if (Direction == (int)EMonsterDirection::Left)
	{
		if (!IsCollide(X - 1, Y))
		{
			X--;
		}
	}
	if (Direction == (int)EMonsterDirection::Right)
	{
		if (!IsCollide(X + 1, Y))
		{
			X++;
		}
	}
	if (Direction == (int)EMonsterDirection::Up)
	{
		if (!IsCollide(X, Y - 1))
		{
			Y--;
		}
	}
	if (Direction == (int)EMonsterDirection::Down)
	{
		if (!IsCollide(X, Y + 1))
		{
			Y++;
		}
	}
}

bool AMonster::IsCollide(int NewX, int NewY)
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
