#pragma once
// 이렇게 클래스 앞에 한번만 해서 사용하던가
class UWorld;

class SimpleEngine
{
public:
	SimpleEngine();
	virtual ~SimpleEngine();

	void Init(); // 엔진 초기화, 언리얼 에서는 GameInstance.Init(); 이런 형태

	void Run();

	void Stop();

	void Term();

	inline UWorld* GetWorld() const { return World; };

protected:
	// 아니면 이렇게 하나하나씩 쓰던가 자유입니다.
	class UWorld* World;
	bool IsRunning;
};

