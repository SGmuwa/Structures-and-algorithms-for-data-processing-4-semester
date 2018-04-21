
#include "z7.16 integral Right Rectangle Method.h"
#include "z7.16 test integral Right Rectangle Method.h"
#include "z7.16 UserInterface.h"

// Функция 16 варианта.
double f_xePsx(double x)
{
	return (x * exp(-x));
}

void BeginIntegral()
{
	printf("xe^-x integral from a = 0, b = select.\n");
	float hCurrent;
	do
		hCurrent = z7_16_UserInterface_GetFloat("Accuracy of calculations: ");
	while (hCurrent <= 0 || isnan(hCurrent));
	printf("b = 0.5; result: %0.46f\n", z7_16_iRRM_CalculateIntegralByH(f_xePsx, 0.0f, 0.5f, hCurrent));
	printf("b = 1.0; result: %0.46f\n", z7_16_iRRM_CalculateIntegralByH(f_xePsx, 0.0f, 1.0f, hCurrent));
	printf("b = 1.5; result: %0.46f\n", z7_16_iRRM_CalculateIntegralByH(f_xePsx, 0.0f, 1.5f, hCurrent));
	printf("b = 2.0; result: %0.46f\n", z7_16_iRRM_CalculateIntegralByH(f_xePsx, 0.0f, 2.0f, hCurrent));

	printf("b: your; result: %0.46f\n", z7_16_iRRM_CalculateIntegralByH(f_xePsx, 0.0f, z7_16_UserInterface_GetFloatInInterval("b = ", -5.0f, 25.0f), hCurrent));
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
