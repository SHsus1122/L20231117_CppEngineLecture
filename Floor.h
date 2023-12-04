#pragma once
#include "Actor.h"
class AFloor : public AActor
{
public:
	AFloor();
	AFloor(int NewX, int NewY, char NewShape = ' ', int NewSortOrder = 1, SDL_Color NewColor = SDL_Color{ 128, 128, 128, 0 });
	virtual ~AFloor();
};

