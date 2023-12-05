#pragma once
#include "Actor.h"
class APlayer : public AActor
{
public:
	APlayer();
	APlayer(int NewX, int NewY, char NewShape = 'P', int NewSortOrder = 500, 
		SDL_Color NewColor = SDL_Color {255, 0, 0, 0}, int NowDirection = 0);
	virtual ~APlayer();

	// Tick ������, �̴� ���͸��� �ϴ����� �ٸ��� ������ �ڽ� ���� �������մϴ�.
	virtual void Tick() override;
	bool IsCollide(int NewX, int NEwY);

	virtual void Render() override;

	Uint64 ProcessTime;
	Uint64 ElaspedTime;		// ��� �ð�

	Uint8 SpriteIndex = 0;
	Uint8 SpriteDirection = 0;
};
