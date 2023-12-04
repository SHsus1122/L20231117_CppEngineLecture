#pragma once
#include "Actor.h"
class AWall : public AActor
{
public:
	AWall();
	// char NewShape = '*' 는 default Agument 라고 기본적으로 생성하게 강제
	AWall(int NewX, int NewY, char NewShape = '*', int NewSortOrder = 100, SDL_Color NewColor = SDL_Color{ 255, 102, 255, 0 });
	virtual ~AWall();
};

