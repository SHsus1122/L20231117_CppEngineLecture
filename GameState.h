#pragma once
#include "Actor.h"
class AGameState : public AActor
{
public:
	AGameState();
	virtual ~AGameState();
	virtual void Render() override;

	bool IsGameOver;
	bool IsNextLevel;
};

