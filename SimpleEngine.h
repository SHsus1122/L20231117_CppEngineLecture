#pragma once
#include <string>
#include "SDL.h"

#pragma comment(lib, "SDL2")
#pragma comment(lib, "SDL2main")


// �̷��� Ŭ���� �տ� �ѹ��� �ؼ� ����ϴ���
// ���� ����(Forward Declaration)
// C++ ������ �̸� �Լ��� �������� ������ ���������� �ڵ带 �о�鿩 ������ �߻���ŵ�ϴ�.(�ĺ��� �̹߰�)
// ������ ��ó�� ���ָ� �ĺ��ڸ� �����ϱ� �� �ĺ����� ���縦 �����Ϸ��� �̸� �˸��� �˴ϴ�.
// �̸� ���� ������ �ð��� �����Ű��, ������� ���� �������� ���߰� �˴ϴ�.(��ȯ������ ����)
// ��������� �ڵ��� ��⼺�� ����Ű�� �˴ϴ�.
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

	void Init();	// ���� �ʱ�ȭ, �𸮾� ������ GameInstance.Init(); �̷� ����

	void Run();

	void Stop();

	void Term();

	void LoadLevel(std::string Filename);	// �𸮾󿡼� UI ���� �þ��� OpenLevel �� ����� ��...?

	inline UWorld* GetWorld() const { return World; };	// ���� ���� ��������
	
	// ó���� null �̱� ������ ����� �˴ϴ�. �׸��� 2���� �� ����� �մϴ�.(�̱��� ����)
	// �� ���� ����.. �� ���� ���� ���������� ��� ����
	static SimpleEngine* GetInstance() { 
		if (Instance == nullptr)
		{
			Instance = new SimpleEngine();
		}
		return Instance; 
	}

	static SDL_Keycode KeyCode;

	// ���漱�� �� �������� ���ؼ�
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
	// �ƴϸ� �̷��� �ϳ��ϳ��� ������ �����Դϴ�.
	UWorld* World;
	bool IsRunning;

	// �Է��� ������ �� �޵� �ۿ� ����Ǹ� �ȵ� ���� int �� ������ �ȵ˴ϴ�. �ֳ��ϸ�, ... ?
	void Input();
	void Tick();
	void Render();

	// �̷��� �������� ����� ����ϱ����� �ݵ�� �ʱ�ȭ�� ����� �մϴ�.
	static SimpleEngine* Instance;

	// ���� ���� ���ݴϴ�. �ʱ�ȭ �� ����ϱ� ���ؼ�
	AGameMode* GameMode;
	AGameState* GameState;

	// ���� ��ġ���� ���� ���ͷ� ����� �޶�� �ǹ��� �Լ�
	void LoadActor(int NewX, int NewY, char Actor);
};

// UE5 ������� �ϴ¹�
#define GEngine SimpleEngine::GetInstance()