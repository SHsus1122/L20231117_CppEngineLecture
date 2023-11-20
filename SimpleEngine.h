#pragma once
#include <string>

// �̷��� Ŭ���� �տ� �ѹ��� �ؼ� ����ϴ���
class UWorld;

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

protected:
	// �ƴϸ� �̷��� �ϳ��ϳ��� ������ �����Դϴ�.
	UWorld* World;
	bool IsRunning;

	// �Է��� ������ �� �޵� �ۿ� ����Ǹ� �ȵ� ���� int �� ������ �ȵ˴ϴ�. �ֳ��ϸ�, ... ?
	int Input();
	void Tick(int KeyCode);
	void Render();

	// �̷��� �������� ����� ����ϱ����� �ݵ�� �ʱ�ȭ�� ����� �մϴ�.
	static SimpleEngine* Instance;
};

// UE5 ������� �ϴ¹�
#define GEngine SimpleEngine::GetInstance()