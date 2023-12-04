#pragma once
#include "Actor.h"
class AGoal : public AActor
{
public:
	AGoal();
	AGoal(int NewX, int NewY, char NewShape = 'G', int NewSortOrder = 200, SDL_Color NewColor = SDL_Color{ 102, 0, 153, 0 });
	virtual ~AGoal();
};

