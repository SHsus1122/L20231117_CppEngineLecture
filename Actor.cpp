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
	SpriteSizeX = 1;	// 나누는것을 기본 전제로 하기 때문에 0으로 나누면 안되니 1로 초기화
	SpriteSizeY = 1;
	Direction = 0;

	ProcessTime = 300;	// 500밀리 세컨드에 한번 씩
	ElaspedTime = 0;
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
	Direction = 0;
	AnimationFrame = 0;
	ProcessTime = 300;	// 500밀리 세컨드에 한번 씩
	ElaspedTime = 0;
}

AActor::~AActor()
{
	SDL_DestroyTexture(MyTexture);	// 기존에 하던것과 마찬가지로 이 둘은 포인터이기 때문에
	SDL_FreeSurface(MySurface);		// 사용했으면 날려주는것도 해줘야 합니다.
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
		// 실행을 했으면 이제 다시 초기화
		ElaspedTime = 0;
	}
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

		//bmp 이전에 테스트용으로 사용했던 코드
		//SDL_SetRenderDrawColor(GEngine->MyRenderer, Color.r, Color.g, Color.b, Color.a);
		//SDL_RenderFillRect(GEngine->MyRenderer, &rect);
		//사각형으로 표시 이전에 표현만을 위해서 사용했던 코드
		//SDL_RenderDrawPoint(GEngine->MyRenderer, X, Y);
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

