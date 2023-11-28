#include "Actor.h"
#include "SimpleEngine.h"
#include "Wall.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

//class NHR
//{
//public:
//	NHR(int NewMoney) {
//		Money = NewMoney;
//	};
//	virtual ~NHR() {}
//
//	int Money;
//
//	// 비교 연산자와 참조 연산자를 활용한 코드로 const 비교만 하고 값의 변경은 X 이기 때문
//	// 아래의 코드에서 부등호를 반대로 하면 또 다른 사이즈의 비교가 됩니다.
//	bool operator>(const NHR& RHS) const
//	{
//		return this->Money > RHS.Money;
//	}
//
//	bool operator<(const NHR& RHS) const
//	{
//		return this->Money < RHS.Money;
//	}
//};
//
//bool compare(const NHR& LHS, const NHR& RHS)
//{
//	if (LHS.Money < RHS.Money)
//	{
//		std::cout << LHS.Money << std::endl;
//		return true;
//	}
//	return false;
//}

// 깃허브 커밋 푸쉬 이메일 계정 불일치 이후 재 테스트
int main()
{
	//vector<NHR> NHRS;

	//NHRS.push_back(NHR(20));
	//NHRS.push_back(NHR(110));
	//NHRS.push_back(NHR(40));
	//NHRS.push_back(NHR(50));
	////sort(NHRS.begin(), NHRS.end());
	////sort(NHRS.begin(), NHRS.end(), [](const NHR& LHS, const NHR& RHS)
	////	{
	////		return LHS.Money < RHS.Money;
	////	});
	//// 값을 가져오되 복사 ㄴㄴ 참조해서 가져와라 const 는 변경 ㄴㄴ
	//sort(NHRS.begin(), NHRS.end(), compare);

	//for (const auto& Data : NHRS)
	//{
	//	cout << Data.Money << endl;
	//}

	 /* 순수 가상 함수 설명
	 virtual void BeginPlay() = 0; 이렇게 순수 함수로 해놓으면
	 아래 처럼 일반적인 생성이 불가능 합니다.(이를 인터페이스 라고 합니다)
	 이렇게 하면 상속 받아서 구현만 합니다. 즉, 부모는 하는일이 없습니다 !
	 AActor A;*/

	SimpleEngine* MyEngine = SimpleEngine::GetInstance();

	// 실행과 상관 없이 메모리에 계속 잡혀있습니다. 글로벌로 사용 !!
	//SimpleEngine::GetInstance();


	// 보통 이 아래 부분을 함수로 뽑아서 재정의 하게 됩니다.
	MyEngine->LoadLevel("Data/level01.smap");
	MyEngine->Run();

	delete MyEngine;


	return 0;
}