#pragma once

#ifndef _INC_Z7_16_TEST_USERINRERFACE
#define _INC_Z7_16_TEST_USERINRERFACE

#ifndef _INC_STDIO
#include <stdio.h>
#endif // !_INC_STDIO

// Печатает сообщение в выходной поток.
// char res: результат. 0: ошибка. Иначе: успех.
// char * message: указатель на начало строки сообщения.
void z7_16_test_UserInterface_p_log(char res, char * message)
{
	if (res == 0) printf("\tError: ");
	printf("%s\n", message);
}

// Печатает сообщение и число в выходной поток.
// char res: результат. 0: ошибка. Иначе: успех.
// char * message: указатель на начало строки сообщения.
// float value: число, которое нужно записать.
void z7_16_test_UserInterface_p_logStringFloat(char res, char * message, float value)
{
	if (res == 0) printf("\tError: ");
	printf("%s%f\n", message, value);
}

// Печатает сообщение и число в выходной поток.
// char res: результат. 0: ошибка. Иначе: успех.
// char * message: указатель на начало строки сообщения.
// unsigned value: число, которое нужно записать.
void z7_16_test_UserInterface_p_logStringUnsignedInt(char res, char * message, unsigned value)
{
	if (res == 0) printf("\tError: ");
	printf("%s%u\n", message, value);
}


#endif // !_INC_Z7_16_TEST_USERINRERFACE
