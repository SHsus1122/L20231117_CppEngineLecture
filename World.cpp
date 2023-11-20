#include "World.h"
#include "Actor.h"	// 월드에서 생성시 액터 사용
#include <algorithm>

UWorld::UWorld()
{
}

UWorld::~UWorld()
{
}

void UWorld::SpawnActor(AActor* NewActor)
{
	if (NewActor)
	{
		Actors.push_back(NewActor);
	}
}

void UWorld::Tick(int KeyCode)
{
	// 레퍼런스 사용법으로 즉, (&)는 값 복사하지 말고 위치를 참조만 하라는 의미
	// 용량이 너무 클 수 있기 때문에 성능에 영향을 미칠 것을 고려해서 하는 참조를 사용합니다.
	// 지금은 아직 필요없기 때문에 이 방식 사용 안함
	//for (const auto &Actor : Actors)
	//{
	//	// 실행만 하고 고치지 말란 의미
	//	Actor->Tick(KeyCode);
	//}
	for (auto Actor : Actors)
	{
		// 실행만 하고 고치지 말란 의미
		Actor->Tick(KeyCode);
	}
}

void UWorld::Render()
{
	for (auto Actor : Actors)
	{
		Actor->Render();
	}
}

// 맵 로딩 끝나고 정렬 하는 함수.. 가.. 됩니다..
void UWorld::SortRenderOrder()
{
	std::sort(Actors.begin(), Actors.end(), [](const AActor* LHS, const AActor* RHS) {
		return LHS->SortOrder < RHS->SortOrder;
		});
}
