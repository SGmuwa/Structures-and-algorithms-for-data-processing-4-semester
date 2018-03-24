#pragma once
#ifndef _INC_Z7_16_INTEGRAL_RIGHT_RECTANGLE_METHOD
#define _INC_Z7_16_INTEGRAL_RIGHT_RECTANGLE_METHOD

#ifndef _INC_MATH
#include <math.h>
#endif // !_INC_MATH


// Получает следующий x.
double z7_16_iRRM_p_getNextX(double oldX, float h);
// Высчитывает сигму.
float z7_16_iRRM_p_sum(unsigned N, float f(float x), float h, float a);
// Получает коэффициент перед сигма.
float z7_16_iRRM_p_getH(float a, float b, unsigned N);

// Высчитывает интеграл функции с определённой точностью.
// float f(float x): подинтегральная функция.
// float a: начальная точка интегрирования.
// float b: конечная точка интегрирования.
// int N: характеристика точности. Чем больше будет это число, тем больше будет итераций, и тем более точным будет результат.
// Возвращает значение интеграла подинтегральной функции в пределах от a до b с некоторой погрешностью.
float z7_16_iRRM_CalculateIntegralByN(float f(float), float a, float b, unsigned N);

// Высчитывает интеграл функции с определённой точностью.
// float f(float x): подинтегральная функция.
// float a: начальная точка интегрирования.
// float b: конечная точка интегрирования.
// int hCurrent: характеристика точности. Чем меньше будет это число, тем больше будет итераций, и тем более точным будет результат.
// Возвращает значение интеграла подинтегральной функции в пределах от a до b с некоторой погрешностью.
float z7_16_iRRM_CalculateIntegralByH(float f(float), float a, float b, float hCurrent);

// ----------------------------------------------------

double z7_16_iRRM_p_getNextX(double oldX, float h)
{ return oldX + h; }

float z7_16_iRRM_p_sum(unsigned N, float f(float x), float h, float a)
{
	double out = 0.0f;
	double OldX = (double)a;
	for (unsigned i = 1; i != N + 1; i++)
	{
		out += (double)f((float)OldX);
		OldX = z7_16_iRRM_p_getNextX(OldX, h);
	}
	return (float)out;
}

float z7_16_iRRM_p_getH(float a, float b, unsigned N)
{ return (b - a) / (float)N; }

float z7_16_iRRM_CalculateIntegralByN(float f(float), float a, float b, unsigned N)
{
	float h = z7_16_iRRM_p_getH(a, b, N);
	return h * z7_16_iRRM_p_sum(N, f, h, a);
}

float z7_16_iRRM_CalculateIntegralByH(float f(float), float a, float b, float hCurrent)
{
	if (isfinite(hCurrent) && hCurrent > 0.0f)
	{
		unsigned N = 1;
		float buffer1 = 0.0f;
		float buffer2 = z7_16_iRRM_CalculateIntegralByN(f, a, b, N);
		do {
			buffer1 = buffer2;
			N *= 2;
			buffer2 = z7_16_iRRM_CalculateIntegralByN(f, a, b, N);
		} while (buffer1 - buffer2 > hCurrent || buffer1 - buffer2 < -hCurrent);
		return buffer2;
	}
	else return nanf((const char *)0);
}

#endif // !_INC_Z7_16_INTEGRAL_RIGHT_RECTANGLE_METHOD