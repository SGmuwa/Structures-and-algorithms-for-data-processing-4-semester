#pragma once

#ifndef Z7_16_INTEGRAL_RIGHT_RECTANGLE_METHOD
#include "z7.16 integral Right Rectangle Method.h"
#endif // !Z7_16_INTEGRAL_RIGHT_RECTANGLE_METHOD

#ifndef INC_Z7_16_TEST_USERINRERFACE
#include "z7.16 test UserInterface.h"
#endif

#define TRUE 1
#define FALSE 0

#define ISNAN(X) ((X) != (X))

// Тестирует z7_16_iRRM_p_getNextX. Возвращает количество ошибок.
unsigned short z7_16_tiRRM_p_Test_p_getNextX()
{
	unsigned short out = 0;
	if (z7_16_iRRM_p_getNextX(0.0f, 0.0f) == 0.0f)
		z7_16_test_UserInterface_p_log(TRUE, "z7_16_iRRM_p_getNextX: 0, 0: ok");
	else
	{
		out++;
		z7_16_test_UserInterface_p_logStringFloat(FALSE, "z7_16_iRRM_p_getNextX: 0, 0: failed. Result: ", z7_16_iRRM_p_getNextX(0.0f, 0.0f));
	}

	if (z7_16_iRRM_p_getNextX(-3.0f, 0.2f) == -2.8f)
		z7_16_test_UserInterface_p_log(TRUE, "z7_16_iRRM_p_getNextX: -3, 0.2: ok");
	else
	{
		out++;
		z7_16_test_UserInterface_p_logStringFloat(FALSE, "z7_16_iRRM_p_getNextX: -3, 0.2: failed. Result: ", z7_16_iRRM_p_getNextX(-3.0f, 0.2f));
	}
	return out;
}

// Тестирует z7_16_iRRM_p_getH. Возвращает количество ошибок.
unsigned short z7_16_tiRRM_p_Test_p_getH()
{
	unsigned short out = 0;

	if (ISNAN(z7_16_iRRM_p_getH(0.0f, 0.0f, 0u)))
		z7_16_test_UserInterface_p_log(TRUE, "z7_16_iRRM_p_getH: 0, 0, 0: ok");
	else
	{
		out++;
		z7_16_test_UserInterface_p_logStringFloat(FALSE, "z7_16_iRRM_p_getH: 0, 0: failed. Result: ", z7_16_iRRM_p_getH(0.0f, 0.0f, 0u));
	}

	if (z7_16_iRRM_p_getH(-4.0f, 7.2f, 4u) == 2.8f)
		z7_16_test_UserInterface_p_log(TRUE, "z7_16_iRRM_p_getH: -3, 0.2: ok");
	else
	{
		out++;
		z7_16_test_UserInterface_p_logStringFloat(FALSE, "z7_16_iRRM_p_getH: -3, 0.2: failed. Result: ", z7_16_iRRM_p_getH(-4.0f, 7.2f, 4));
	}

	return out;
}

float z7_16_tiRRM_p_Test_p_sum_functionArgument1(float x) { return 1.0f; }
float z7_16_tiRRM_p_Test_p_sum_functionArgument2(float x) { return x; }

// Тестирует z7_16_iRRM_p_sum. Возвращает количество ошибок.
unsigned short z7_16_tiRRM_p_Test_p_sum()
{
	unsigned short out = 0;
	if (z7_16_iRRM_p_sum(0, z7_16_tiRRM_p_Test_p_sum_functionArgument1, 1.0f) == 0.0f)
		z7_16_test_UserInterface_p_log(TRUE, "z7_16_iRRM_p_sum: 0, f1, 1.0: ok");
	else
	{
		out++;
		z7_16_test_UserInterface_p_logStringFloat(FALSE, "z7_16_iRRM_p_sum: 0, f1, 1.0: failed. Result: ", z7_16_iRRM_p_sum(0, z7_16_tiRRM_p_Test_p_sum_functionArgument1, 1.0f));
	}

	if (z7_16_iRRM_p_sum(3, z7_16_tiRRM_p_Test_p_sum_functionArgument2, 1.0f) == 6.0f) // Смотреть примечание 1 в коде
		z7_16_test_UserInterface_p_log(TRUE, "z7_16_iRRM_p_sum: 3, f2, 1.0: ok");
	else
	{
		out++;
		z7_16_test_UserInterface_p_logStringFloat(FALSE, "z7_16_iRRM_p_sum:  3, f2, 1.0: failed. Result: ", z7_16_iRRM_p_sum(3, z7_16_tiRRM_p_Test_p_sum_functionArgument2, 1.0f));
	}
	return out;
}

unsigned short z7_16_tiRRM_p_Test_CalculateIntegral()
{
	unsigned short out = 0;
	float buffer;

	buffer = z7_16_iRRM_CalculateIntegral(z7_16_tiRRM_p_Test_p_sum_functionArgument2, 0.0f, 16.0f, 1000);
	if (buffer - 128.0f < 0.1f && buffer - 128.0f > -0.1f)
		z7_16_test_UserInterface_p_log(TRUE, "z7_16_iRRM_CalculateIntegral: f2, 0, 16, 1000.");
	else
	{
		out++;
		z7_16_test_UserInterface_p_logStringFloat(FALSE, "z7_16_iRRM_CalculateIntegral: f2, 0, 16, 1000: failed. Observational error: ", buffer - 128.0f);
	}

	buffer = z7_16_iRRM_CalculateIntegral(z7_16_tiRRM_p_Test_p_sum_functionArgument2, 0.0f, 0.0f, 0);
	if (ISNAN(buffer))
		z7_16_test_UserInterface_p_log(TRUE, "z7_16_iRRM_CalculateIntegral: f2, 0, 0, 0: isnan.");
	else
	{
		out++;
		z7_16_test_UserInterface_p_logStringFloat(FALSE, "z7_16_iRRM_CalculateIntegral:  f2, 0, 0, 0: failed. Result: ", buffer);
	}

	return out;
}


unsigned short z7_16_tiRRM_StartTest()
{
	unsigned short total = 0;
	z7_16_test_UserInterface_p_log(TRUE, "test z7_16_iRRM started.");
	total += z7_16_tiRRM_p_Test_p_getNextX();
	total += z7_16_tiRRM_p_Test_p_getH();
	total += z7_16_tiRRM_p_Test_p_sum();
	total += z7_16_tiRRM_p_Test_CalculateIntegral();
	z7_16_test_UserInterface_p_logStringFloat(total == 0.0f, "test z7_16_iRRM ended. Total errors: ", (float)total);
	return total;
}

/*

z7_16_test_UserInterface_p_log(0, "z7_16_tiRRM_p_getH: 0, 0: failed. Result: ");
char buffer[32] = { 0 };
if(
#ifdef _MSC_VER
sprintf_s(buffer, sizeof(buffer), "%f", p_getNextX(0, 0))
#else
sprintf(buffer, "%f", p_getNextX(0, 0))
#endif // _MSC_VER
== 1) z7_16_test_UserInterface_p_log(1, buffer);
else z7_16_test_UserInterface_p_log(0, "error to write Result.");


*/



/*
Примичание 1.
Вычисление суммы из 3 членов с заданной функцией.
sum(i = 1 ... n, f(x(oldX, h)))

oldX = 0;
Пусть unsigned N = 3

Пусть flaot h = 1

x(1) = 0 + h = h = 1
x(2) = x(1) + h = 0 + 2h = 2h = 2
x(3) = x(2) + h = 0 + 3h = 3h = 3

f(x) = x

f(1) = 1
f(2) = 2
f(3) = 3

sum = 1 + 2 + 3 = 3 + 3 = 6.

Ответ: 6.

*/