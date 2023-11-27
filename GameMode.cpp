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
	// 부모의 것을 구현해줍니다.
	AActor::Tick();
	static APlayer* MyPlayer = nullptr;
	static AGoal* MyGoal = nullptr;
	static AMonster* MyMonster = nullptr;
	if (!MyGoal || !MyPlayer)
	{
		// 지금은 골이라는 목적지가 하나인 경우에만 한 것이고 이것이 두개가 되거나 늘어나면 또 코드가 달라져야 합니다.
		for (auto Actor : GEngine->GetWorld()->GetAllActors())
		{
			APlayer* TempMyPlayer = dynamic_cast<APlayer*>(Actor);
			// Actor is Player? 라는 의미입니다.
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

	// 둘 다 찾은 경우가 됩니다.
	// 또 현재 위치가 골의 위치와 같은지에 대한 조건식이 됩니다.
	if (MyPlayer && MyMonster &&
		MyMonster->GetX() == MyPlayer->GetX() &&
		MyMonster->GetY() == MyPlayer->GetY())
	{
		std::cout << "Complete" << std::endl;
		GEngine->Stop();
		// 게임을 끝내거나, 다음 레벨로 이동하거나 등..
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
		// 게임을 끝내거나, 다음 레벨로 이동하거나 등..
	}
}
*/