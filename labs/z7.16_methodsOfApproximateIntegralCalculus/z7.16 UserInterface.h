
#ifndef _INC_Z7_16_USERINTERFACE
#define _INC_Z7_16_USERINTERFACE

#ifndef _INC_STDIO
#include <stdio.h>
#endif // !_INC_STDIO

#define TRUE 1
#define FALSE 0

// Запрашивает у пользователя один символ информации, что вызывает остановку программы и её ожидание.
void z7_16_UserInterface_Pause()
{
#ifdef _MSC_VER
	scanf_s("%*c");
#else
	scanf("%*c");
#endif
}

// Отправляет пользователю сообщение, и ожидает у него ответа от 0 до maxAccess.
// const char * message: Указатель на сообщение.
// unsigned char maxAccess: Максимально допустимое значение.
// Возвращает: Число, введёное пользователем с клавиатуры в пределах 0...maxAccess.
unsigned char z7_16_UserInterface_GetChek(const char * message, unsigned char maxAccess)
{
	unsigned char buffer = 0;
	while (TRUE)
	{
#ifdef _MSC_VER
		printf_s("%s", message);
#else
		printf("%s", message);
#endif // _MSC_VER
		if (
#ifdef _MSC_VER
			scanf_s("%hhu", &buffer)
#else
			scanf("%hhu", &buffer)
#endif // _MSC_VER
			>= 1 // Не совсем уверен, как работает %*s. Поэтому знак >=.
			&& // Сработает, если компилатор проверяет слева на право выражения. Иначе: будет баг в использовании.
			buffer <= maxAccess)
		{
			break;
		}
		if (buffer == 0)
		{
#ifdef _MSC_VER
			scanf_s("%*s");
#else
			scanf("%*s");
#endif // _MSC_VER
		}
		buffer = 0;
	}
#ifdef _MSC_VER
	scanf_s("%*c");
#else
	scanf("%*c");
#endif // _MSC_VER
	return buffer;
}

// Запрашивает целое беззнаковое число у пользователя.
// const char * message: сообщение, которое увидит пользователь.
// Возвращает: Целое беззнаковое число, которое передал пользователь или поток.
unsigned z7_16_UserInterface_GetUnsignedInt(const char * message)
{
	unsigned buffer = 0;
	while(TRUE)
	{
#ifdef _MSC_VER
		printf_s("%s", message);
#else
		printf("%s", message);
#endif // _MSC_VER
		if (
#ifdef _MSC_VER
			scanf_s("%u", &buffer)
#else
			scanf("%u", &buffer)
#endif // _MSC_VER
			>= 1 // Не совсем уверен, как работает %*s. Поэтому знак >=.
			)
		{
			break;
		}
#ifdef _MSC_VER
		scanf_s("%*s");
#else
		scanf("%*s");
#endif // _MSC_VER
	}
#ifdef _MSC_VER
	scanf_s("%*c");
#else
	scanf("%*c");
#endif // _MSC_VER
	return buffer;
}

// Запрашивает целое вещественное число у пользователя.
// const char * message: сообщение, которое увидит пользователь.
// Возвращает: Вещественное число, которое передал пользователь или поток.
float z7_16_UserInterface_GetFloat(const char * message)
{
	float buffer = 0;
	while (TRUE)
	{
#ifdef _MSC_VER
		printf_s("%s", message);
#else
		printf("%s", message);
#endif // _MSC_VER
		if (
#ifdef _MSC_VER
			scanf_s("%f", &buffer)
#else
			scanf("%f", &buffer)
#endif // _MSC_VER
			>= 1 // Не совсем уверен, как работает %*s. Поэтому знак >=.
			)
		{
			break;
		}
#ifdef _MSC_VER
		scanf_s("%*s");
#else
		scanf("%*s");
#endif // _MSC_VER
	}
#ifdef _MSC_VER
	scanf_s("%*c");
#else
	scanf("%*c");
#endif // _MSC_VER
	return buffer;
}

#endif // !_INC_Z7_16_USERINTERFACE

