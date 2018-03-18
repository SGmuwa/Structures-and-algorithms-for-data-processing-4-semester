#pragma once
#ifndef Z7_16_INTEGRAL_RIGHT_RECTANGLE_METHOD
#define Z7_16_INTEGRAL_RIGHT_RECTANGLE_METHOD

// Получает следующий x.
float z7_16_iRRM_p_getNextX(float oldX, float h);
// Высчитывает сигму.
float z7_16_iRRM_p_sum(unsigned N, float f(float x), float h);
// Получает коэффициент перед сигма.
float z7_16_iRRM_p_getH(float a, float b, unsigned N);

// Высчитывает интеграл функции с определённой точностью.
// float(*f)(float x): подинтегральная функция.
// float a: начальная точка интегрирования.
// float b: конечная точка интегрирования.
// int N: характеристика точности. Чем больше будет это число, тем больше будет итераций, и тем более точным будет результат.
// Возвращает значение интеграла подинтегральной функции в пределах от a до b с некоторой погрешностью.
float z7_16_iRRM_CalculateIntegral(float(*f)(float x), float a, float b, unsigned N);




#endif // !Z7_16_INTEGRAL_RIGHT_RECTANGLE_METHOD