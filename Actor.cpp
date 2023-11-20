#include "Actor.h"
#include <windows.h>
#include <iostream>

// Shape 초기값 빈값으로 자식에서 값을 넣을 겁니다.
AActor::AActor() :
	X(0), Y(0), Shape(' '), SortOrder(0), bCollide(false)
{
	// 아무런 값이 들어가는 경우를 방지하기 위해서 초기화
	//X = 0;
	//Y = 0;
}

// 아래의 방식이 accessor 의 사용법의 예시입니다.
AActor::AActor(int NewX, int NewY)
{
	SetX(NewX);
	SetY(NewY);
	Shape = ' ';
	SortOrder = 0;
	bCollide = false;
}

AActor::~AActor()
{
}

void AActor::BeginPlay()
{
}

void AActor::Tick(int KeyCode)
{
}

void AActor::Render()
{
	// 현재 액터 위치에 모양 출력
	COORD Cur;
	Cur.X = X;
	Cur.Y = Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);

	// 그리기 위한 정보 모양 값이 필요합니다.(스테틱 메시, 스켈레탈 메쉬 등)
	std::cout << Shape;
}

