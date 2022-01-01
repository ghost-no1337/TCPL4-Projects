#include "SI Unit.h"

int main()
{
	auto distance = 10.0_m;
	auto time = 20.0_s;
	auto speed = distance / time;

	//if (speed == 20)
	//if (speed == distance)
	//if (speed == 10_m / 20_s)

	Quantity<MpS2> acceleration = distance / square(time);

	cout << "speed==" << speed << " acceleration==" << acceleration << "\n";
}