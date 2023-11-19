#pragma once
class AActor
{
public:
	AActor();
	virtual ~AActor();

	// 뒤에 0을 붙이면 순수 함수라고 구현을 강제합니다.
	// virtual void BeginPlay() = 0;
	virtual void BeginPlay();
	virtual void Tick();
	virtual void Render();
};

