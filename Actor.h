#pragma once
#include "SDL.h"
#include <iostream>

class AActor
{
public:
	AActor();
	AActor(int NewX, int NewY);	// ������ �����ε�(������) ���ڸ� �ٸ��� �ؼ� ���� !
	virtual ~AActor();

	// �ڿ� 0�� ���̸� ���� �Լ���� ������ �����մϴ�.
	// virtual void BeginPlay() = 0;
	virtual void BeginPlay();
	virtual void Tick();
	virtual void Render();

	// accessor
	// �̸� ����ϴ� ������ �ٸ������ �̸� ����� �� �ʱⰪ�� ���ִ� ���� �ִ� ���� �����ϱ� ���ؼ��Դϴ�.
	// ������ ���÷� �����ֱ� ���Ŀ� ������ �����Դϴ�.
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

	// Uint �� �Ϲ����� int �� �ٸ��� SDL ���� Ư�� ũ��� ��ȣ ���� ������ ��Ÿ���ϴ�.
	// ������ �ٸ��ĸ� �̷��� �ϸ� ũ�ν� �÷��� �� �پ��� ȯ�濡�� �ϰ��� ũ���� ��������� �����մϴ�.
	Uint16 Size;
	int Direction;
	int AnimationFrame;

	SDL_Surface* MySurface;  // �̹��� �����͸� ���� ǥ��
	SDL_Texture* MyTexture;  // �������� �̹����� �ؽ�ó

	bool bIsSprite;   // bmp �̹��� �߶� �����ؼ� ����ϴ��� ���� Ȯ�ο� ����
	int SpriteSizeX;  // bmp �̹��� �ڸ��� ���� X
	int SpriteSizeY;  // bmp �̹��� �ڸ��� ���� Y

	virtual void LoadBMP(std::string Filename, SDL_Color ColorKey = SDL_Color{ 255, 255, 255, 0 });

	Uint32 ProcessTime;
	Uint32 ElaspedTime;		// ��� �ð�
protected:
	int X;
	int Y;

	char Shape;
};

