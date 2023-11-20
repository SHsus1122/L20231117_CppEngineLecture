#pragma once
#include "Actor.h"
class APlayer : public AActor
{
public:
	APlayer();
	APlayer(int NewX, int NewY, char NewShape = 'P', int NewSortOrder = 500);
	virtual ~APlayer();

	// Tick 재정의, 이는 액터마다 하는일이 다르기 때문에 자식 것을 재정의합니다.
	virtual void Tick(int KeyCode) override;
	bool IsCollide(int NewX, int NEwY);
};

