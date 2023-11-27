#include "GameMode.h"
#include "Player.h"
#include "Goal.h"
#include "SimpleEngine.h"
#include "World.h"
#include "Monster.h"
#include <iostream>
#include "GameState.h"

AGameMode::AGameMode()
{
	SortOrder = 1000;
}

AGameMode::~AGameMode()
{
}

void AGameMode::Tick() //Server
{
	AActor::Tick();

	if (SimpleEngine::GetGameState()->IsNextLevel)
	{
		std::cout << "Complete" << std::endl;
		GEngine->Stop();
	}

	if (SimpleEngine::GetGameState()->IsGameOver)
	{
		std::cout << "GameOver" << std::endl;
		GEngine->Stop();
	}

}

/*
void AGameMode::Tick()
{
	// �θ��� ���� �������ݴϴ�.
	AActor::Tick();
	static APlayer* MyPlayer = nullptr;
	static AGoal* MyGoal = nullptr;
	static AMonster* MyMonster = nullptr;
	if (!MyGoal || !MyPlayer)
	{
		// ������ ���̶�� �������� �ϳ��� ��쿡�� �� ���̰� �̰��� �ΰ��� �ǰų� �þ�� �� �ڵ尡 �޶����� �մϴ�.
		for (auto Actor : GEngine->GetWorld()->GetAllActors())
		{
			APlayer* TempMyPlayer = dynamic_cast<APlayer*>(Actor);
			// Actor is Player? ��� �ǹ��Դϴ�.
			if (TempMyPlayer)
			{
				MyPlayer = TempMyPlayer;
			}

			AGoal* TempMyGoal = dynamic_cast<AGoal*>(Actor);
			if (TempMyGoal)
			{
				MyGoal = TempMyGoal;
			}

			AMonster* TempMyMonster = dynamic_cast<AMonster*>(Actor);
			if (TempMyMonster)
			{
				MyMonster = TempMyMonster;
			}
		}
	}

	// �� �� ã�� ��찡 �˴ϴ�.
	// �� ���� ��ġ�� ���� ��ġ�� �������� ���� ���ǽ��� �˴ϴ�.
	if (MyPlayer && MyMonster &&
		MyMonster->GetX() == MyPlayer->GetX() &&
		MyMonster->GetY() == MyPlayer->GetY())
	{
		std::cout << "Complete" << std::endl;
		GEngine->Stop();
		// ������ �����ų�, ���� ������ �̵��ϰų� ��..
	}
	
	if (SimpleEngine::)
	{

	}

	if (MyGoal && MyPlayer &&
		MyGoal->GetX() == MyPlayer->GetX() &&
		MyGoal->GetY() == MyPlayer->GetY())
	{
		std::cout << "Complete" << std::endl;
		GEngine->Stop();
		// ������ �����ų�, ���� ������ �̵��ϰų� ��..
	}
}
*/