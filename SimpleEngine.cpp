
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
		// �۾� ���� �� �����
		// Input
		// Tick
		// Render
		// World; // ��� ���ư��� �ؼ�
	}
}

void SimpleEngine::Stop()
{
	IsRunning = false;
}

void SimpleEngine::Term()
{
}
