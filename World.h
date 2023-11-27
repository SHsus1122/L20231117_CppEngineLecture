#pragma once
#include <vector>	// 액터를 담기 위해서 사용

class AActor;		// 액터

class UWorld
{
public:
	UWorld();
	virtual ~UWorld();

	void SpawnActor(AActor* NewActor);	// 액터생성

	void Tick();
	void Render();

	void SortRenderOrder();

	const std::vector<AActor*>& GetAllActors()
	{
		return Actors;
	}
protected:
	std::vector<AActor*> Actors;
};

