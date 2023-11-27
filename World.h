#pragma once
#include <vector>	// ���͸� ��� ���ؼ� ���

class AActor;		// ����

class UWorld
{
public:
	UWorld();
	virtual ~UWorld();

	void SpawnActor(AActor* NewActor);	// ���ͻ���

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

