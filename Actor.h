#pragma once
class AActor
{
public:
	AActor();
	AActor(int NewX, int NewY);	// ������ �����ε�(������) ���ڸ� �ٸ��� �ؼ� ���� !
	virtual ~AActor();

	// �ڿ� 0�� ���̸� ���� �Լ���� ������ �����մϴ�.
	// virtual void BeginPlay() = 0;
	virtual void BeginPlay();
	virtual void Tick(int KeyCode);
	virtual void Render();

	// accessor
	// �̸� ����ϴ� ������ �ٸ������ �̸� ����� �� �ʱⰪ�� ���ִ� ���� �ִ� ���� �����ϱ� ���ؼ��Դϴ�.
	// ������ ���÷� �����ֱ� ���Ŀ� ������ �����Դϴ�.
	inline int GetX() const { return X; }
	inline int GetY() const { return Y; }

	inline void SetX(int NewX) { X = NewX; }
	inline void SetY(int NewY) { Y = NewY; }

	inline bool operator<(const AActor* RHS) const
	{
		return this->SortOrder < RHS->SortOrder;
	}

	inline bool operator>(const AActor* RHS) const
	{
		return this->SortOrder < RHS->SortOrder;
	}

	int SortOrder;
	bool bCollide;

protected:
	int X;
	int Y;

	char Shape;
};

