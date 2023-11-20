#pragma once
#include <string>

// 이렇게 클래스 앞에 한번만 해서 사용하던가
class UWorld;

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

protected:
	// 아니면 이렇게 하나하나씩 쓰던가 자유입니다.
	UWorld* World;
	bool IsRunning;

	// 입력은 엔진이 안 받되 밖에 노출되면 안됨 원래 int 로 받으면 안됩니다. 왜냐하면, ... ?
	int Input();
	void Tick(int KeyCode);
	void Render();

	// 이렇게 정적으로 만들면 사용하기전에 반드시 초기화를 해줘야 합니다.
	static SimpleEngine* Instance;
};

// UE5 방식으로 하는법
#define GEngine SimpleEngine::GetInstance()