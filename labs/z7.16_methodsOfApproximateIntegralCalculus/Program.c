﻿
#include "z7.16 integral Right Rectangle Method.h"
#include "z7.16 test integral Right Rectangle Method.h"
#include "z7.16 UserInterface.h"
#include <math.h>

float f_xePsx(float x)
{
	return x * exp((double)-x);
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
	unsigned N = z7_16_UserInterface_GetUnsignedInt("Number of iterations: ");
	printf("result: %f\n", z7_16_iRRM_CalculateIntegral(f_xePsx, 0.0f, b, N));
}

void main(void)
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
}