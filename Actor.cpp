#include "Actor.h"
#include <windows.h>
#include <iostream>

// Shape �ʱⰪ ������ �ڽĿ��� ���� ���� �̴ϴ�.
AActor::AActor() :
	X(0), Y(0), Shape(' '), SortOrder(0), bCollide(false)
{
	// �ƹ��� ���� ���� ��츦 �����ϱ� ���ؼ� �ʱ�ȭ
	//X = 0;
	//Y = 0;
}

// �Ʒ��� ����� accessor �� ������ �����Դϴ�.
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
	// ���� ���� ��ġ�� ��� ���
	COORD Cur;
	Cur.X = X;
	Cur.Y = Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);

	// �׸��� ���� ���� ��� ���� �ʿ��մϴ�.(����ƽ �޽�, ���̷�Ż �޽� ��)
	std::cout << Shape;
}

