#pragma once
#ifndef _INC_Z7_16_INTEGRAL_RIGHT_RECTANGLE_METHOD
#define _INC_Z7_16_INTEGRAL_RIGHT_RECTANGLE_METHOD

#ifndef _INC_MATH
#include <math.h>
#endif // !_INC_MATH


// Получает следующий x.
inline double z7_16_iRRM_p_getNextX(double oldX, double h);
// Рассчитывает сигму.
double z7_16_iRRM_p_sum(unsigned long N, double f(double x), double h, float a);
// Получает коэффициент перед сигма.
double z7_16_iRRM_p_getH(float a, float b, unsigned long N);

// Рассчитывает интеграл функции с определённой точностью.
// double f(double): подынтегральная функция.
// float a: начальная точка интегрирования.
// float b: конечная точка интегрирования.
// unsigned long N: характеристика точности. Чем больше будет это число, тем больше будет итераций, и тем более точным будет результат.
// Возвращает значение интеграла подынтегральной функции в пределах от a до b с некоторой погрешностью.
double z7_16_iRRM_CalculateIntegralByN(double f(double), float a, float b, unsigned long N);

// Рассчитывает интеграл функции с определённой точностью.
// double f(double): подынтегральная функция.
// float a: начальная точка интегрирования.
// float b: конечная точка интегрирования.
// float hCurrent: характеристика точности. Чем меньше будет это число, тем больше будет итераций, и тем более точным будет результат.
// Возвращает значение интеграла подынтегральной функции в пределах от a до b с некоторой погрешностью.
double z7_16_iRRM_CalculateIntegralByH(double f(double), float a, float b, float hCurrent);

// ----------------------------------------------------

inline double z7_16_iRRM_p_getNextX(double oldX, double h)
{ return oldX + h; }

double z7_16_iRRM_p_sum(unsigned long N, double f(double x), double h, float a)
{
	double out = 0.0f;
	double OldX = (double)a;
	for (unsigned long i = 1; i != N + 1; i++)
	{
		out += f(OldX);
		OldX = z7_16_iRRM_p_getNextX(OldX, h);
	}
	return out;
}

double z7_16_iRRM_p_getH(float a, float b, unsigned long N)
{ return ((double)b - (double)a) / N; }

double z7_16_iRRM_CalculateIntegralByN(double f(double), float a, float b, unsigned long N)
{
	double h = z7_16_iRRM_p_getH(a, b, N);
	return h * z7_16_iRRM_p_sum(N, f, h, a);
}

double z7_16_iRRM_CalculateIntegralByH(double f(double), float a, float b, float hCurrent)
{
	if (isfinite(hCurrent) && hCurrent > 0.0f)
	{
		unsigned long N = 1;
		double buffer1 = 0.0f;
		double buffer2 = z7_16_iRRM_CalculateIntegralByN(f, a, b, N);
		do {
			buffer1 = buffer2;
			N *= 2;
			if (N == 0) // В случае, если счётчик вышел за пределы.
				return (float)nan(&buffer2);
			buffer2 = z7_16_iRRM_CalculateIntegralByN(f, a, b, N);
		} while (buffer1 - buffer2 > hCurrent || buffer1 - buffer2 < -hCurrent);
		return buffer2;
	}
	else return nanf((const char *)0);
}

#endif // !_INC_Z7_16_INTEGRAL_RIGHT_RECTANGLE_METHOD