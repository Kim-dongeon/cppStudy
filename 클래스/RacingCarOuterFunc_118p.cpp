#include <iostream>
using namespace std;

namespace CAR_CONST
{
	enum
	{
		ID_LEN = 20,
		MAX_SPD = 200,
		FUEL_STEP = 2,
		ACC_STRP = 10,
		BRK_STRP =10
	};
}
struct car
{
	char gamerID[CAR_CONST::ID_LEN];
	int fuelGauge;
	int curSpeed;

	void ShowCarState();
	void Accel();
	void Break();
};

void car::ShowCarState()
{
	cout << "소유자 ID: " << gamerID << endl;
	cout << "연료량 : " << fuelGauge << "%" << endl;
	cout << "현재속도 : " << curSpeed << "km/s" << endl << endl;
}
void car::Accel()
{
	if (fuelGauge <= 0)
	{
		return;
	}
	else
	{
		fuelGauge -= CAR_CONST::FUEL_STEP;
	}
	if ((curSpeed + CAR_CONST::ACC_STRP) >= CAR_CONST::MAX_SPD)
	{
		curSpeed = CAR_CONST::MAX_SPD;
		return;
	}

	curSpeed += CAR_CONST::ACC_STRP;
}
void car::Break()
{
	if (curSpeed < CAR_CONST::BRK_STRP)
	{
		curSpeed = 0;
		return;
	}
	curSpeed -= CAR_CONST::BRK_STRP;
}
int main()
{
	car run99 = { "run99",100,0 };
	run99.Accel();
	run99.ShowCarState();
	run99.Break();
	run99.ShowCarState();
	return 0;
}