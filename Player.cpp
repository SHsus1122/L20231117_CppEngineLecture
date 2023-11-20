#include "Player.h"
#include <iostream>
#include <windows.h>
#include "World.h"
#include "SimpleEngine.h"

APlayer::APlayer()
{
	Shape = 'P';
	X = 10;
	Y = 10;
	SortOrder = 500;
}

APlayer::APlayer(int NewX, int NewY, char NewShape, int NewSortOrder)
{
	Shape = 'P';
	SetX(NewX);
	SetY(NewY);
	SortOrder = NewSortOrder;
}

APlayer::~APlayer()
{
}

void APlayer::Tick(int KeyCode)
{
	//AActor::Tick(KeyCode);	// 부모의 것을 호출합니다. 이것이 정규 문법입니다.
	__super::Tick(KeyCode);	// 이것도 동일하나 비주얼 스튜디오(MS) 한정입니다.
	
	// 우리는 충돌 관련은 빼고.. 움직임만... 아래처럼 상하좌우 움직임을 구현하게 됩니다.
	// 이제 이를 움직임은 컴포넌트에서 하기 때문에 추후에 컴포넌트 로직으로 변경하게 될 겁니다.
	if (KeyCode == 'A' || KeyCode == 'a')
	{
		if (!IsCollide(X - 1, Y))
		{
			X--;
		}
	}
	if (KeyCode == 'D' || KeyCode == 'd')
	{
		if (!IsCollide(X + 1, Y))
		{
			X++;
		}
	}
	if (KeyCode == 'W' || KeyCode == 'w')
	{
		if (!IsCollide(X, Y - 1))
		{
			Y--;
		}
	}
	if (KeyCode == 'S' || KeyCode == 's')
	{
		if (!IsCollide(X, Y + 1))
		{
			Y++;
		}
	}
}

bool APlayer::IsCollide(int NewX, int NewY)
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
