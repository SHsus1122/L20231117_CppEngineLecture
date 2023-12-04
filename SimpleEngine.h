#pragma once
#include <string>
#include "SDL.h"

#pragma comment(lib, "SDL2")
#pragma comment(lib, "SDL2main")


// 이렇게 클래스 앞에 한번만 해서 사용하던가
// 전방 선언(Forward Declaration)
// C++ 에서는 미리 함수를 정의하지 않으면 순차적으로 코드를 읽어들여 오류를 발생시킵니다.(식별자 미발견)
// 하지만 이처럼 해주면 식별자를 정의하기 전 식별자의 존재를 컴파일러에 미리 알리게 됩니다.
// 이를 통해 컴파일 시간을 단축시키며, 헤더파일 간의 의존성을 낮추게 됩니다.(순환참조도 방지)
// 결과적으로 코드의 모듈성을 향상시키게 됩니다.
class UWorld;
class AActor;
class AGameMode;
class AGameState;

class SimpleEngine
{
private:
	SimpleEngine();
public:
	//SimpleEngine();
	virtual ~SimpleEngine();

	void Init();	// 엔진 초기화, 언리얼 에서는 GameInstance.Init(); 이런 형태

	void Run();

	void Stop();

	void Term();

	void LoadLevel(std::string Filename);	// 언리얼에서 UI 에서 봤었던 OpenLevel 과 비슷한 듯...?

	inline UWorld* GetWorld() const { return World; };	// 월드 정보 가져오기
	
	// 처음엔 null 이기 때문에 만들게 됩니다. 그리고 2개씩 못 만들게 합니다.(싱글톤 패턴)
	// 장 단점 존재.. 한 번만 만들어서 여러곳에서 사용 가능
	static SimpleEngine* GetInstance() { 
		if (Instance == nullptr)
		{
			Instance = new SimpleEngine();
		}
		return Instance; 
	}

	static SDL_Keycode KeyCode;

	// 전방선언 후 가져오기 위해서
	static AGameState* GetGameState()
	{
		return GetInstance()->GameState;
	}

	static AGameMode* GetGameMode()
	{
		return GetInstance()->GameMode;
	}

	static Uint64 GetWorldDeltaSeconds()
	{
		return GetInstance()->DeltaSeconds;
	}

	SDL_Window* MyWindow;
	SDL_Renderer* MyRenderer;
	SDL_Event MyEvent;
	Uint64 DeltaSeconds;
	Uint64 LastTime;

protected:
	// 아니면 이렇게 하나하나씩 쓰던가 자유입니다.
	UWorld* World;
	bool IsRunning;

	// 입력은 엔진이 안 받되 밖에 노출되면 안됨 원래 int 로 받으면 안됩니다. 왜냐하면, ... ?
	void Input();
	void Tick();
	void Render();

	// 이렇게 정적으로 만들면 사용하기전에 반드시 초기화를 해줘야 합니다.
	static SimpleEngine* Instance;

	// 전방 선언 해줍니다. 초기화 때 사용하기 위해서
	AGameMode* GameMode;
	AGameState* GameState;

	// 현재 위치에서 무슨 액터로 만들어 달라는 의미의 함수
	void LoadActor(int NewX, int NewY, char Actor);
};

// UE5 방식으로 하는법
#define GEngine SimpleEngine::GetInstance()