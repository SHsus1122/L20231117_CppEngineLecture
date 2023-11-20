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
	//AActor::Tick(KeyCode);	// �θ��� ���� ȣ���մϴ�. �̰��� ���� �����Դϴ�.
	__super::Tick(KeyCode);	// �̰͵� �����ϳ� ���־� ��Ʃ���(MS) �����Դϴ�.
	
	// �츮�� �浹 ������ ����.. �����Ӹ�... �Ʒ�ó�� �����¿� �������� �����ϰ� �˴ϴ�.
	// ���� �̸� �������� ������Ʈ���� �ϱ� ������ ���Ŀ� ������Ʈ �������� �����ϰ� �� �̴ϴ�.
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
