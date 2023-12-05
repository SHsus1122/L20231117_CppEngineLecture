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

	// Uint 는 일반적인 int 랑 다르게 SDL 에서 특정 크기와 부호 없는 정수를 나타냅니다.
	// 무엇이 다르냐면 이렇게 하면 크로스 플랫폼 및 다양한 환경에서 일관된 크기의 정수사용이 가능합니다.
	Uint16 Size;
	int Direction;
	int AnimationFrame;

	SDL_Surface* MySurface;  // 이미지 데이터를 담을 표면
	SDL_Texture* MyTexture;  // 렌더링할 이미지의 텍스처

	bool bIsSprite;   // bmp 이미지 잘라서 분할해서 사용하는지 여부 확인용 변수
	int SpriteSizeX;  // bmp 이미지 자르는 비율 X
	int SpriteSizeY;  // bmp 이미지 자르는 비율 Y

	virtual void LoadBMP(std::string Filename, SDL_Color ColorKey = SDL_Color{ 255, 255, 255, 0 });

	Uint32 ProcessTime;
	Uint32 ElaspedTime;		// 경과 시간
protected:
	int X;
	int Y;

	char Shape;
};

