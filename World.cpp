#include "World.h"
#include "Actor.h"	// ���忡�� ������ ���� ���
#include <algorithm>

UWorld::UWorld()
{
}

UWorld::~UWorld()
{
	// �̸� ���ִ� ������ ���ʹ� ���忡 ���Ѱ��̸� ���������� ��������� å�����ݴϴ�.
	for (auto Actor : Actors)
	{
		delete Actor;
	}
	Actors.clear();
}

void UWorld::SpawnActor(AActor* NewActor)
{
	if (NewActor)
	{
		Actors.push_back(NewActor);
	}
}

void UWorld::Tick()
{
	// ���۷��� �������� ��, (&)�� �� �������� ���� ��ġ�� ������ �϶�� �ǹ�
	// �뷮�� �ʹ� Ŭ �� �ֱ� ������ ���ɿ� ������ ��ĥ ���� ����ؼ� �ϴ� ������ ����մϴ�.
	// ������ ���� �ʿ���� ������ �� ��� ��� ����
	//for (const auto &Actor : Actors)
	//{
	//	// ���ุ �ϰ� ��ġ�� ���� �ǹ�
	//	Actor->Tick(KeyCode);
	//}
	for (auto Actor : Actors)
	{
		// ���ุ �ϰ� ��ġ�� ���� �ǹ�
		Actor->Tick();
	}
}

void UWorld::Render()
{
	for (auto Actor : Actors)
	{
		Actor->Render();
	}
}

// �� �ε� ������ ���� �ϴ� �Լ�.. ��.. �˴ϴ�..
void UWorld::SortRenderOrder()
{
	std::sort(Actors.begin(), Actors.end(), [](const AActor* LHS, const AActor* RHS) {
		return LHS->SortOrder < RHS->SortOrder;
		});
}
