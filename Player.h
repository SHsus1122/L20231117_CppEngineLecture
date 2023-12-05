#pragma once
#include "Actor.h"
class APlayer : public AActor
{
public:
	APlayer();
	APlayer(int NewX, int NewY, char NewShape = 'P', int NewSortOrder = 500, 
		SDL_Color NewColor = SDL_Color {255, 0, 0, 0}, int NowDirection = 0);
	virtual ~APlayer();

	// Tick 재정의, 이는 액터마다 하는일이 다르기 때문에 자식 것을 재정의합니다.
	virtual void Tick() override;
	bool IsCollide(int NewX, int NEwY);

	virtual void Render() override;

	Uint64 ProcessTime;
	Uint64 ElaspedTime;		// 경과 시간

	Uint8 SpriteIndex = 0;
	Uint8 SpriteDirection = 0;
};
