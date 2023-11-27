#pragma once
#include "Actor.h"
class AMonster : public AActor
{
public:
	AMonster();
	AMonster(int NewX, int NewY, char NewShape = 'M', int NewSortOrder = 300);
	virtual ~AMonster();

	virtual void Tick() override;
	bool IsCollide(int NewX, int NEwY);
};

enum class EMonsterDirection
{
	Left = 0,
	Right = 1,
	Down = 2,
	Up = 3
};
