#include "Actor.h"
#include <windows.h>
#include <iostream>
#include "SimpleEngine.h"
#include "Player.h"

AActor::AActor() :
	X(0), Y(0), Shape(' '), SortOrder(0), bCollide(false), Size(50), AnimationFrame(0)
{
	MySurface = nullptr;
	MyTexture = nullptr;
	bIsSprite = false;
	Color = SDL_Color {};
	SpriteSizeX = 1;	// �����°��� �⺻ ������ �ϱ� ������ 0���� ������ �ȵǴ� 1�� �ʱ�ȭ
	SpriteSizeY = 1;
	Direction = 0;

	ProcessTime = 300;	// 500�и� �����忡 �ѹ� ��
	ElaspedTime = 0;
}

// �Ʒ��� ����� accessor �� ������ �����Դϴ�.
AActor::AActor(int NewX, int NewY)
{
	SetX(NewX);
	SetY(NewY);
	Shape = ' ';
	SortOrder = 0;
	bCollide = false;
	Size = 50;
	MySurface = nullptr;
	MyTexture = nullptr;
	bIsSprite = false;
	SpriteSizeX = 1;
	SpriteSizeY = 1;
	Direction = 0;
	AnimationFrame = 0;
	ProcessTime = 300;	// 500�и� �����忡 �ѹ� ��
	ElaspedTime = 0;
}

AActor::~AActor()
{
	SDL_DestroyTexture(MyTexture);	// ������ �ϴ��Ͱ� ���������� �� ���� �������̱� ������
	SDL_FreeSurface(MySurface);		// ��������� �����ִ°͵� ����� �մϴ�.
}

void AActor::BeginPlay()
{
}

void AActor::Tick()
{
	ElaspedTime += GEngine->GetWorldDeltaSeconds();
	if (ElaspedTime <= ProcessTime)
	{
		return;
	}
	else
	{
		AnimationFrame += Size;
		if (AnimationFrame > 200)
		{
			AnimationFrame = 0;
		}
		// ������ ������ ���� �ٽ� �ʱ�ȭ
		ElaspedTime = 0;
	}
}

void AActor::Render()
{
	// ���� ���� ��ġ�� ��� ���
	COORD Cur;
	Cur.X = X;
	Cur.Y = Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);

	// �׸��� ���� ���� ��� ���� �ʿ��մϴ�.(����ƽ �޽�, ���̷�Ż �޽� ��)
	//std::cout << Shape;

	SDL_Rect rect;		// �ڽ� ���� ����
	rect.x = X * Size;	// ���簢���� ���� �� �𼭸��� x ��ġ
	rect.y = Y * Size;	// ���簢���� ���� �� �𼭸��� y ��ġ
	rect.w = Size;		// ���簢���� �ʺ�
	rect.h = Size;		// ���簢���� ����

	// �Ʒ��� �ڵ尡 VRAM -> Screen �ϴ� ���̰� �̴� VRAM �����߿� �ִ� ���� �Űܼ� �׸��� ���� ���մϴ�.
	if (bIsSprite)
	{
		SDL_RenderCopy(GEngine->MyRenderer,
			MyTexture,
			new SDL_Rect{ AnimationFrame, Size * Direction, MySurface->w / SpriteSizeX, MySurface->h / SpriteSizeY },
			new SDL_Rect{ X * Size, Y * Size, Size , Size });
	}
	else
	{
		SDL_RenderCopy(GEngine->MyRenderer,
			MyTexture,
			nullptr,
			new SDL_Rect{ X * Size, Y * Size, Size , Size });
	}

		//bmp ������ �׽�Ʈ������ ����ߴ� �ڵ�
		//SDL_SetRenderDrawColor(GEngine->MyRenderer, Color.r, Color.g, Color.b, Color.a);
		//SDL_RenderFillRect(GEngine->MyRenderer, &rect);
		//�簢������ ǥ�� ������ ǥ������ ���ؼ� ����ߴ� �ڵ�
		//SDL_RenderDrawPoint(GEngine->MyRenderer, X, Y);
}

void AActor::LoadBMP(std::string Filename, SDL_Color ColorKey)
{
	// �Ʒ��� �ڵ��� �ǹ̴� SSD -> RAM ���� �ű�ٴ� �ǹ��Դϴ�.
	MySurface = SDL_LoadBMP(Filename.c_str());	// ���� �ε��ؼ� MySurface ���� �Ѱ��شٴ� �ǹ�

	// �̹��� ���� �� ��� ������ �� ������ �����ִ� ���� 255, 255, 255, 0 �� �κ��Դϴ�. �Ͼ� ����� 255.. �����°� 0 ����
	SDL_SetColorKey(MySurface, 
		SDL_TRUE, 
		SDL_MapRGBA(MySurface->format, ColorKey.r, ColorKey.g, ColorKey.b, ColorKey.a));

	// ���� ���� �޸𸮷� �ű�� ���� �ʿ��մϴ�. �̷��ԵǸ� �� �ٲ�µ� �̸� Texture ��� �մϴ�.
	// ���� ������ ������ �ε��ؼ� GPU �� �ű� �Ϳ� �ش��մϴ�.
	MyTexture = SDL_CreateTextureFromSurface(GEngine->MyRenderer, MySurface);
}

