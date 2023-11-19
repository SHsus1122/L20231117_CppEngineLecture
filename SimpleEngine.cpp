
#include "SimpleEngine.h"

SimpleEngine::SimpleEngine()
{
}

SimpleEngine::~SimpleEngine()
{
	IsRunning = true;
}

void SimpleEngine::Init()
{
}

void SimpleEngine::Run()
{
	while (IsRunning)
	{
		// 작업 순서 및 내용들
		// Input
		// Tick
		// Render
		// World; // 계속 돌아가야 해서
	}
}

void SimpleEngine::Stop()
{
	IsRunning = false;
}

void SimpleEngine::Term()
{
}
