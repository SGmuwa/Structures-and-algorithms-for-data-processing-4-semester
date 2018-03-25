
#include "z7.16 integral Right Rectangle Method.h"
#include "z7.16 test integral Right Rectangle Method.h"
#include "z7.16 UserInterface.h"
#include <math.h>

float f_xePsx(float x)
{
	return (float)(x * exp((double)-x));
}

void BeginIntegral()
{
	float b;
	printf("xe^-x integral from a = 0, b = select.\n");
	switch (z7_16_UserInterface_GetChek("0. b = 0.5.\n1. b = 1.0\n2. b = 1.5.\n3. b = 2.0.\n", 3))
	{
	case 0:
		b = 0.5f;
		break;
	case 1:
		b = 1.0f;
		break;
	case 2:
		b = 1.5f;
		break;
	default:
		b = 2.0f;
	}
	float hCurrent;
	do
		hCurrent = z7_16_UserInterface_GetFloat("Accuracy of calculations: ");
	while (hCurrent <= 0 || isnan(hCurrent));
	printf("result: %f\n", z7_16_iRRM_CalculateIntegralByH(f_xePsx, 0.0f, b, hCurrent));
}

int main(int argc, char * argv[])
{
	switch (z7_16_UserInterface_GetChek("0. Launch the lab work #1.\n1. Perform functional testing.\n", 1))
	{
	case 0:
		BeginIntegral();
		break;
	default:
		z7_16_tiRRM_StartTest();
	}
	z7_16_UserInterface_Pause();
	return 0;
}
