#pragma once
class AActor
{
public:
	AActor();
	virtual ~AActor();

	// �ڿ� 0�� ���̸� ���� �Լ���� ������ �����մϴ�.
	// virtual void BeginPlay() = 0;
	virtual void BeginPlay();
	virtual void Tick();
	virtual void Render();
};

