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
//	// �� �����ڿ� ���� �����ڸ� Ȱ���� �ڵ�� const �񱳸� �ϰ� ���� ������ X �̱� ����
//	// �Ʒ��� �ڵ忡�� �ε�ȣ�� �ݴ�� �ϸ� �� �ٸ� �������� �񱳰� �˴ϴ�.
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

// ����� Ŀ�� Ǫ�� �̸��� ���� ����ġ ���� �� �׽�Ʈ
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
	//// ���� �������� ���� ���� �����ؼ� �����Ͷ� const �� ���� ����
	//sort(NHRS.begin(), NHRS.end(), compare);

	//for (const auto& Data : NHRS)
	//{
	//	cout << Data.Money << endl;
	//}

	 /* ���� ���� �Լ� ����
	 virtual void BeginPlay() = 0; �̷��� ���� �Լ��� �س�����
	 �Ʒ� ó�� �Ϲ����� ������ �Ұ��� �մϴ�.(�̸� �������̽� ��� �մϴ�)
	 �̷��� �ϸ� ��� �޾Ƽ� ������ �մϴ�. ��, �θ�� �ϴ����� �����ϴ� !
	 AActor A;*/

	SimpleEngine* MyEngine = SimpleEngine::GetInstance();

	// ����� ��� ���� �޸𸮿� ��� �����ֽ��ϴ�. �۷ι��� ��� !!
	//SimpleEngine::GetInstance();


	// ���� �� �Ʒ� �κ��� �Լ��� �̾Ƽ� ������ �ϰ� �˴ϴ�.
	MyEngine->LoadLevel("Data/level01.smap");
	MyEngine->Run();

	delete MyEngine;


	return 0;
}