#pragma once
#include "SDL.h"
#include <iostream>

class AActor
{
public:
	AActor();
	AActor(int NewX, int NewY);	// 생성자 오버로딩(재정의) 인자만 다르게 해서 적용 !
	virtual ~AActor();

	// 뒤에 0을 붙이면 순수 함수라고 구현을 강제합니다.
	// virtual void BeginPlay() = 0;
	virtual void BeginPlay();
	virtual void Tick();
	virtual void Render();

	// accessor
	// 이를 사용하는 이유는 다른사람이 이를 사용할 때 초기값에 못넣는 값을 넣는 것을 방지하기 위해서입니다.
	// 지금은 예시로 보여주기 추후에 삭제할 예정입니다.
	inline int GetX() const { return X; }
	inline int GetY() const { return Y; }

	inline void SetX(int NewX) { X = NewX; }
	inline void SetY(int NewY) { Y = NewY; }

	virtual bool operator<(const AActor& RHS) const
	{
		return this->SortOrder < RHS.SortOrder;
	}

	virtual bool operator>(const AActor& RHS) const
	{
		return this->SortOrder > RHS.SortOrder;
	}

	SDL_Color Color;

	int SortOrder;
	bool bCollide;

	Uint16 Size;

	SDL_Surface* MySurface;
	SDL_Texture* MyTexture;

	bool bIsSprite;
	int SpriteSizeX;
	int SpriteSizeY;

	virtual void LoadBMP(std::string Filename, SDL_Color ColorKey = SDL_Color{ 255, 255, 255, 0 });

protected:
	int X;
	int Y;

	char Shape;
};

