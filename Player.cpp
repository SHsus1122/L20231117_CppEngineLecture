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
	//AActor::Tick(KeyCode);	// �θ��� ���� ȣ���մϴ�. �̰��� ���� �����Դϴ�.
	__super::Tick();	// �̰͵� �����ϳ� ���־� ��Ʃ���(MS) �����Դϴ�.
	//int KeyCode = SimpleEngine::KeyCode;
	int KeyCode = GEngine->MyEvent.key.keysym.sym;
	
	// Ű �Է��� �������� ����� �ǹ�
	if (GEngine->MyEvent.type == SDL_KEYDOWN)
	{
		return;
	}

	if (SimpleEngine::GetGameState()->IsGameOver)
	{
		return;
	}

	// �츮�� �浹 ������ ����.. �����Ӹ�... �Ʒ�ó�� �����¿� �������� �����ϰ� �˴ϴ�.
	// ���� �̸� �������� ������Ʈ���� �ϱ� ������ ���Ŀ� ������Ʈ �������� �����ϰ� �� �̴ϴ�.
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
			// �÷��̾ ���� �ߴٴ� ���� �ǹ��ϸ� �̸� �˷��ֱ⸸ �ϰ� ó���� �ٸ� ������ ���ϰ� �˴ϴ�.
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
