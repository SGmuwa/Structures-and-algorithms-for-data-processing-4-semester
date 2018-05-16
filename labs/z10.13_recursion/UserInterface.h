/*
Sidorenko, Mikhail Pavlovich ([SG]Muwa)
Moscow Technological University
12.05.2018
*/

#include <stdio.h>

float UserInterface_getNaNFloat()
{
	float output = 0;
	unsigned char * ibuffer = (unsigned char *)&output;
	ibuffer[0] = 255;
	ibuffer[1] = 255;
	ibuffer[2] = 255;
	ibuffer[3] = 0;
	return output;
}

unsigned char UserInterface_GetChek(const char * message, unsigned char maxAccess, FILE * fpIN/* = stdin*/, FILE * fpOUT/* = stdout*/)
{
	unsigned char buffer = ~(unsigned char)0u;
	unsigned char tryLimit = 0;
	if (fpIN == NULL) return 0;
	while (--tryLimit != 0)
	{
		if (fpOUT != NULL && message != NULL)
#ifdef _MSC_VER
			fprintf_s(fpOUT, "%s", message);
#else
			fprintf(fpOUT, "%s", message);
#endif // _MSC_VER
		if (
#ifdef _MSC_VER
			fscanf_s(fpIN, "%hhu", &buffer)
#else
			fscanf(fpIN, "%hhu", &buffer)
#endif // _MSC_VER
			>= 1 // Не совсем уверен, как работает %*s. Поэтому знак >=.
			&& // Сработает, если компилатор проверяет слева на право выражения. Иначе: будет баг в использовании.
			buffer <= maxAccess)
		{
			break;
		}
		if (buffer == ~'\0')
		{
#ifdef _MSC_VER
			fscanf_s(fpIN, "%*s");
#else
			fscanf(fpIN, "%*s");
#endif // _MSC_VER
		}
		buffer = ~(unsigned char)0u;
	}
#ifdef _MSC_VER
	fscanf_s(fpIN, "%*c");
#else
	fscanf(fpIN, "%*c");
#endif // _MSC_VER
	return buffer;
}

unsigned UserInterface_GetUnsignedInt(const char * message)
{
	unsigned buffer = 0;
	unsigned char tryLimit = 0;
	while (--tryLimit != 0)
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

// Получает от fpIN число с плавающей точкой.
// const char * message: Сообщение, которое необходимо вывести. В Случае NULL сообщение не будет выведено.
// FILE * fpIN: Поток ввода информация. В случае NULL функция вернёт NaN.
// FILE * fpOUT: Поток вывода информации. В случае NULL сообщение не будет выведено.
// Возвращает: прочитанное от пользователя число.
// Ошибки: если пользователь ошибётся 255 раз, то функция вернёт NaN.
float UserInterface_fGetFloat(const char * message, FILE * fpIN, FILE * fpOUT)
{
	if (fpIN == NULL) return UserInterface_getNaNFloat();
	unsigned char tryLimit = 0;
	float buffer = UserInterface_getNaNFloat();
	while (--tryLimit != 0)
	{
		if (fpOUT != NULL)
#ifdef _MSC_VER
			fprintf_s(fpOUT, "%s", message);
#else
			fprintf(fpOUT, "%s", message);
#endif // _MSC_VER
		if (
#ifdef _MSC_VER
			fscanf_s(fpIN, "%f", &buffer)
#else
			fscanf(fpIN, "%f", &buffer)
#endif // _MSC_VER
			>= 1 // Не совсем уверен, как работает %*s. Поэтому знак >=.
			)
		{
			break;
		}
#ifdef _MSC_VER
		fscanf_s(fpIN, "%*s");
#else
		fscanf(fpIN, "%*s");
#endif // _MSC_VER
	}
#ifdef _MSC_VER
	fscanf_s(fpIN, "%*c");
#else
	fscanf(fpIN, "%*c");
#endif // _MSC_VER
	return buffer;
}

// Получает от стандартного ввода-вывода число с плавающей точкой.
// const char * message: Сообщение, которое необходимо вывести. В случае NULL сообщение не будет выведено.
// Возвращает: прочитанное от пользователя число.
// Ошибки: если пользователь ошибётся 255 раз, то функция вернёт NaN.
float UserInterface_GetFloat(const char * message)
{ return UserInterface_fGetFloat(message, stdin, stdout); }


// Запрашивает текстовые данные от пользователя. Для того, чтобы закончить набирать текстовую информацию, пользователю необходимо отправить любой из следующий символов: \0 \1 \2 \3 \4 \5 \6 \7 \8.
// const char * message: Сообщение, которое нужно вывести перед запросом. В случае NULL сообщение не будет выведено.
// char * To: Указатель на первый доступный символ для записи. В случае NULL функция вернёт 0.
// size_t countTo: Количество доступных символов для записи в To; В случае 0 функция выведет message и вернёт 0.
// FILE * fpIN: Поток ввода информации. Отсюда будет браться текст. В случае NULL функция вернёт 0.
// FILE * fpOUT: Поток вывода информации. В случае NULL сообщение выведено не будет.
// Возвращает: количество прочтённых символов.
size_t UserInterface_fGetStr(const char * message, char * To, size_t countTo, FILE * fpIN, FILE * fpOUT)
{
	if (fpIN == NULL) return 0u;
	if (fpOUT != NULL && message != NULL) fprintf(fpOUT, "%s Use CTRL + 2 or CTRL + A, CTRL + B, CTRL + D for end.\n", message);
	if (To == NULL) return 0u;
	if (countTo == 0u) return 0u;
	char * i = To - 1; // Уменьшаем на 1, так как в цикле будет прибавление
	do {
#ifdef _MSC_VER // Для компилятора Visual Studio
		fread_s(++i, i - To + 1, sizeof(char), 1, fpIN);
#else // Для компиляторов ANSI C.
		fread(++i, sizeof(char), 1, fpIN); // На каждой новой итерации прибавляем i и записываем 1 символ в To.
#endif // _MSC_VER
	} while (*i >= 0x09 && i != To + countTo - 2); // -1 из-за того, что sizeof возвращает количество, а не последний элемент.
												   // -1 из-за того, чтобы не вошёл в цикл и не стал записьвать в 256 элемент.
												   // неактуально: -1 из-за того, чтобы добавить ещё нулевой символ.
												   // Цикл повторяется, пока пользователь не введёт какой-либо управляющий символ.
												   // https://ru.wikipedia.org/wiki/Управляющие_символы

	*(i) = '\0'; // Добавляем последний символ.
	return i - To + 1; // +1 так как нужно количество элементов, а не расстояние между первым и последним.
}

// Запрашивает текстовые данные от пользователя через стандартные потоки ввода-вывода. Для того, чтобы закончить набирать текстовую информацию, пользователю необходимо отправить любой из следующий символов: \0 \1 \2 \3 \4 \5 \6 \7 \8.
// const char * message: Сообщение, которое нужно вывести перед запросом. В случае NULL сообщение не будет выведено.
// char * To: Указатель на первый доступный символ для записи. В случае NULL функция вернёт 0.
// size_t countTo: Количество доступных символов для записи в To; В случае 0 функция выведет message и вернёт 0.
// Возвращает: количество прочтённых символов.
size_t UserInterface_GetStr(const char * message, char * To, size_t countTo)
{
	return UserInterface_fGetStr(message, To, countTo, stdin, stdout);
}

int UserInterface_fGetInt(const char * message, FILE * fpIN, FILE * fpOUT)
{
	if (fpIN == NULL) return 0;
	signed buffer = 0;
	unsigned char tryLimit = 0;
	while (--tryLimit != 0)
	{
		if (fpOUT != NULL)
#ifdef _MSC_VER
			fprintf_s(fpOUT, "%s", message);
#else
			fprintf(fpOUT, "%s", message);
#endif // _MSC_VER
		if (
#ifdef _MSC_VER
			fscanf_s(fpIN, "%d", &buffer)
#else
			fscanf(fpIN, "%d", &buffer)
#endif // _MSC_VER
			>= 1 // Не совсем уверен, как работает %*s. Поэтому знак >=.
			)
		{
			break;
		}
#ifdef _MSC_VER
		fscanf_s(fpIN, "%*s");
#else
		fscanf(fpIN, "%*s");
#endif // _MSC_VER
	}
#ifdef _MSC_VER
	fscanf_s(fpIN, "%*c");
#else
	fscanf(fpIN, "%*c");
#endif // _MSC_VER
	return buffer;
}



unsigned UserInterface_GetUnsignedIntLimit(const char * message, unsigned min, unsigned max)
{
	if (min > max) return min;
	unsigned buffer;
	do
	{
		buffer = UserInterface_GetUnsignedInt(message);
	} while (buffer < min || buffer > max);
	return buffer;
}

void UserInterface_fPause(const char * message, FILE * fpIN, FILE * fpOUT)
{
#ifdef _MSC_VER
	if(fpOUT != NULL && message != NULL)
		fprintf_s(fpOUT, "%s", message);
	if (fpIN == NULL)
		for (unsigned int i = ~0u; i != 0; --i);
	else
		fscanf_s(fpIN, "%*c");
#else
	if (fpOUT != NULL && message != NULL)
		fprintf(fpOUT, "%s", message);
	if (fpIN == NULL)
		for (unsigned int i = ~0u; i != 0; --i);
	else
		fscanf(fpIN, "%*c");
#endif // _MSC_VER
}

void UserInterface_Pause(const char * message)
{
	UserInterface_fPause(message, stdin, stdout);
}
