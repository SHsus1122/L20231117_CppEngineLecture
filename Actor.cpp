#include "Actor.h"
#include <windows.h>
#include <iostream>
#include "SimpleEngine.h"

// Shape �ʱⰪ ������ �ڽĿ��� ���� ���� �̴ϴ�.
AActor::AActor() :
	X(0), Y(0), Shape(' '), SortOrder(0), bCollide(false), Size(50)
{
	MySurface = nullptr;
	MyTexture = nullptr;
	bIsSprite = false;
	Color = SDL_Color {};
	SpriteSizeX = 1;
	SpriteSizeY = 1;
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
	Size = 50;
	MySurface = nullptr;
	MyTexture = nullptr;
	bIsSprite = false;
	SpriteSizeX = 1;
	SpriteSizeY = 1;
}

AActor::~AActor()
{
	SDL_DestroyTexture(MyTexture);
	SDL_FreeSurface(MySurface);
}

void AActor::BeginPlay()
{
}

void AActor::Tick()
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
			new SDL_Rect{ 0, 0, MySurface->w / SpriteSizeX, MySurface->h / SpriteSizeY },
			new SDL_Rect{ X * Size, Y * Size, Size , Size });
	}
	else
	{
		SDL_RenderCopy(GEngine->MyRenderer,
			MyTexture,
			nullptr,
			new SDL_Rect{ X * Size, Y * Size, Size , Size });
	}

		//SDL_SetRenderDrawColor(GEngine->MyRenderer, Color.r, Color.g, Color.b, Color.a);
		//SDL_RenderFillRect(GEngine->MyRenderer, &rect);

		//SDL_RenderDrawPoint(GEngine->MyRenderer, X, Y);

		/*
		SDL_Rect image_hitbox;
	SDL_Texture* image = IMG_LoadTexture(renderer, filelocation.c_str());
	���� �̹��� ��ü�� ũ�⸦ ������� �ʰ� �̹����� Ư�� ũ��� ǥ���Ϸ��� �Ϲ�ó�� �����ϸ� �˴ϴ�.

	image_hitbox.x = locationX;
	image_hitbox.y = locationY;
	image_hitbox.w = width;
	image_hitbox.h = height;
	�ʺ�� ���̰� �׸� ��ü�� ���� �޶������� �Ϸ��� ������ �����Ͻʽÿ�.

	SDL_QueryTexture(image, nullptr, nullptr, &image_hitbox.w, &image_hitbox.h);
	�ؽ�ó �ʺ�� ���̸� ���� �� �ֽ��ϴ�.

	�׷� ���� �̹����� ������ �������Ϸ��� ������ �����մϴ�.

	SDL_RenderCopy(renderer, image, nullptr, &image_hitbox);
	SDL_RenderPresent(renderer);
		*/

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

