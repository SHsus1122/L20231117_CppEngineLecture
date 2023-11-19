#pragma once
// �̷��� Ŭ���� �տ� �ѹ��� �ؼ� ����ϴ���
class UWorld;

class SimpleEngine
{
public:
	SimpleEngine();
	virtual ~SimpleEngine();

	void Init(); // ���� �ʱ�ȭ, �𸮾� ������ GameInstance.Init(); �̷� ����

	void Run();

	void Stop();

	void Term();

	inline UWorld* GetWorld() const { return World; };

protected:
	// �ƴϸ� �̷��� �ϳ��ϳ��� ������ �����Դϴ�.
	class UWorld* World;
	bool IsRunning;
};

