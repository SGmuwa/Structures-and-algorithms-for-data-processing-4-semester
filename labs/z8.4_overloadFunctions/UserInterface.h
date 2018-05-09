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
	// FILE * fpIN: указатель на поток ввода информации в программу. В случае NULL функция вернёт 0 и завершит работу без изменений.
	// FILE * fpOUT: указатель на поток вывода информации из программы.
	// Возвращает: количество прочтённых символов, включая последний нуливой.
	static size_t GetStr(const char * message, char * To, size_t countTo, FILE * fpIN, FILE * fpOUT);

	// Запрашивает целое число у пользователя.
	// const char * message: сообщение, которое увидит пользователь.
	// FILE * fpIN: указатель на поток ввода информации в программу. В случае NULL функция вернёт 0.
	// FILE * fpOUT: указатель на поток вывода информации из программы.
	// Возвращает: Целое число, которое передал пользователь или поток.
	static signed GetInt(const char * message, FILE * fpIN, FILE * fpOUT);

	// Запрашивает целое беззнаковое число у пользователя в определённом интервале.
	// char * message: сообщение, которое увидит пользователь.
	// unsigned min: минимальное допустимое значение.
	// unsigned max: макисмальное допустимое значение.
	// Возвращает: Целое беззнаковое число, которое передал пользователь или поток.
	static unsigned GetUnsignedInt(const char * message, unsigned min, unsigned max);

	// Приостанавливает поток.
	// const char * message = NULL: Указатель на первый символ сообщения, который надо вывести перед паузой. В случае NULL, сообщение не будет выведено.
	// FILE * fpOUT = stdout: указатель на структуру файла, куда отправляется сообщение перед паузой. В случае NULL сообщение не будет отправлено. По-умолчанию stdout.
	// FILE * fpIN = stdin: указатель на структуру файла, откуда идёт ожидание. По-умолчанию stdin. В случае, если указать NULL, то поток будет ожидать, пока процессор отсчитает int от начала до конца.
	static void pause(const char * message = NULL, FILE * fpOUT = stdout, FILE * fpIN = stdin);
};

#endif //!_INC_USERINTERFACE_