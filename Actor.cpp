#include "Actor.h"
#include <windows.h>
#include <iostream>
#include "SimpleEngine.h"

// Shape 초기값 빈값으로 자식에서 값을 넣을 겁니다.
AActor::AActor() :
	X(0), Y(0), Shape(' '), SortOrder(0), bCollide(false), Size(50)
{
	MySurface = nullptr;
	MyTexture = nullptr;
	bIsSprite = false;
	Color = SDL_Color {};
	SpriteSizeX = 1;
	SpriteSizeY = 1;
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
	// 현재 액터 위치에 모양 출력
	COORD Cur;
	Cur.X = X;
	Cur.Y = Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);

	// 그리기 위한 정보 모양 값이 필요합니다.(스테틱 메시, 스켈레탈 메쉬 등)
	//std::cout << Shape;

	SDL_Rect rect;		// 박스 영역 지정
	rect.x = X * Size;	// 직사각형의 왼쪽 위 모서리의 x 위치
	rect.y = Y * Size;	// 직사각형의 왼쪽 위 모서리의 y 위치
	rect.w = Size;		// 직사각형의 너비
	rect.h = Size;		// 직사각형의 높이

	// 아래의 코드가 VRAM -> Screen 하는 것이고 이는 VRAM 영역중에 있는 것을 옮겨서 그리는 것을 말합니다.
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
	이제 이미지 자체의 크기를 고려하지 않고 이미지를 특정 크기로 표시하려면 일반처럼 설정하면 됩니다.

	image_hitbox.x = locationX;
	image_hitbox.y = locationY;
	image_hitbox.w = width;
	image_hitbox.h = height;
	너비와 높이가 그림 자체에 따라 달라지도록 하려면 다음을 수행하십시오.

	SDL_QueryTexture(image, nullptr, nullptr, &image_hitbox.w, &image_hitbox.h);
	텍스처 너비와 높이를 얻을 수 있습니다.

	그런 다음 이미지를 간단히 렌더링하려면 다음을 수행합니다.

	SDL_RenderCopy(renderer, image, nullptr, &image_hitbox);
	SDL_RenderPresent(renderer);
		*/

}

void AActor::LoadBMP(std::string Filename, SDL_Color ColorKey)
{
	// 아래의 코드의 의미는 SSD -> RAM 으로 옮긴다는 의미입니다.
	MySurface = SDL_LoadBMP(Filename.c_str());	// 파일 로딩해서 MySurface 으로 넘겨준다는 의미

	// 이미지 파일 뒷 배경 날리기 이 배경색을 정해주는 것은 255, 255, 255, 0 이 부분입니다. 하얀 배경을 255.. 날리는걸 0 으로
	SDL_SetColorKey(MySurface, 
		SDL_TRUE, 
		SDL_MapRGBA(MySurface->format, ColorKey.r, ColorKey.g, ColorKey.b, ColorKey.a));

	// 이제 비디오 메모리로 옮기는 것이 필요합니다. 이렇게되면 용어가 바뀌는데 이를 Texture 라고 합니다.
	// 여기 까지의 과정이 로딩해서 GPU 로 옮긴 것에 해당합니다.
	MyTexture = SDL_CreateTextureFromSurface(GEngine->MyRenderer, MySurface);

}

