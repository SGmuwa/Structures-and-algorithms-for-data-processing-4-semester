#pragma once

#ifndef _INC_Z8_4_TEST_USERINRERFACE
#define _INC_Z8_4_TEST_USERINRERFACE

#ifndef _INC_STDIO
#include <stdio.h>
#endif // !_INC_STDIO


namespace z8_4
{
	class test_UserInterface
	{
	public:
		// Печатает сообщение в выходной поток.
		// bool res: результат. False: ошибка. Иначе: успех.
		// char * message: указатель на начало строки сообщения.
		static void log(bool res, char * message)
		{
			if (res == false) printf("\tError: %s\n", message);
			if (res == true) printf("%s ok.\n", message);
		}

		// Печатает сообщение и число в выходной поток.
		// bool res: результат. False: ошибка. Иначе: успех.
		// char * message: указатель на начало строки сообщения.
		// float value: число, которое нужно записать.
		static void log(bool res, char * message, float value)
		{
			if (res == false) printf("\tError: %s%f\n", message, value);
			if (res == true) printf("%s%f ok.\n", message, value);
		}

		// Печатает сообщение и число в выходной поток.
		// bool res: результат. False: ошибка. Иначе: успех.
		// char * message: указатель на начало строки сообщения.
		// unsigned value: число, которое нужно записать.
		static void log(bool res, char * message, unsigned value)
		{
			if (res == false) printf("\tError: %s%u\n", message, value);
			if (res == true) printf("%s%u ok.\n", message, value);
		}

		// Печатает сообщение и число в выходной поток.
		// bool res: результат. False: ошибка. Иначе: успех.
		// char * message: указатель на начало строки сообщения.
		// int value: число, которое нужно записать.
		static void log(bool res, char * message, int value)
		{
			if (res == false) printf("\tError: %s%d\n", message, value);
			if (res == true) printf("%s%d ok.\n", message, value);
		}
	};
}
#endif // !_INC_Z8_4_TEST_USERINRERFACE
