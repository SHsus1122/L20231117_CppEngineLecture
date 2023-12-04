#pragma once
#include "Actor.h"
class AMonster : public AActor
{
public:
	AMonster();
	AMonster(int NewX, int NewY, char NewShape = 'M', int NewSortOrder = 300, SDL_Color NewColor = SDL_Color{ 0, 255, 0, 0 });
	virtual ~AMonster();

	virtual void Tick() override;
	bool IsCollide(int NewX, int NEwY);

	
	Uint32 ProcessTime;

	Uint32 ElaspedTime;		// 경과 시간
};

enum class EMonsterDirection
{
	Left = 0,
	Right = 1,
	Down = 2,
	Up = 3
};
