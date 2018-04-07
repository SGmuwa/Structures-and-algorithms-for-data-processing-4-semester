#pragma once

#ifndef _INC_USERINTERFACE_
#define _INC_USERINTERFACE_

#ifndef _INC_STDIO
#include <stdio.h>
#endif
#pragma once

class UserInterface
{
public:
	// Отправляет пользователю сообщение, и ожидает у него ответа от 0 до maxAccess.
	// char * message: Указатель на сообщение.
	// unsigned char maxAccess: Максимально допустимое значение.
	// FILE * fpIN: Входной поток. Обычно stdin. Оставьте NULL, но в таком случае функция вернёт 0.
	// FILE * fpOUT: Выходной поток. Обычно stdout. Оставьте NULL, чтобы никуда не отправлять выходное сообщение.
	// Возвращает: Число, введёное пользователем с клавиатуры в пределах 0...maxAccess.
	static unsigned char GetChek(const char * message, unsigned char maxAccess, FILE * fpIN = stdin, FILE * fpOUT = stdout);

	// Запрашивает целое беззнаковое число у пользователя.
	// char * message: сообщение, которое увидит пользователь.
	// Возвращает: Целое беззнаковое число, которое передал пользователь или поток.
	static unsigned GetUnsignedInt(const char * message);

	// Запрашивает целое вещественное число у пользователя.
	// char * message: сообщение, которое увидит пользователь.
	// Возвращает: Вещественное число, которое передал пользователь или поток.
	static float GetFloat(const char * message, FILE * fpIN, FILE * fpOUT);

	// Получение строки от пользователя с поддержкой остановки.
	// char * message: сообщение, которое увидит пользователь.
	// char * To: указатель, который указывает на тот участок памяти, куда нужно записать результат
	// size_t countTo: количество доступных байт в To.
	// FILE * fpIN: указать поток ввода информации в программу.
	// Возвращает: количество прочтённых символов, включая последний нуливой.
	static size_t GetStr(const char * message, char * To, size_t countTo, FILE * fpIN, FILE * fpOUT);

	// Запрашивает целое число у пользователя.
	// const char * message: сообщение, которое увидит пользователь.
	// Возвращает: Целое число, которое передал пользователь или поток.
	static unsigned GetInt(const char * message);

	// Запрашивает целое беззнаковое число у пользователя в определённом интервале.
	// char * message: сообщение, которое увидит пользователь.
	// unsigned min: минимальное допустимое значение.
	// unsigned max: макисмальное допустимое значение.
	// Возвращает: Целое беззнаковое число, которое передал пользователь или поток.
	static unsigned GetUnsignedInt(char * message, unsigned min, unsigned max);
};

#endif //!_INC_USERINTERFACE_