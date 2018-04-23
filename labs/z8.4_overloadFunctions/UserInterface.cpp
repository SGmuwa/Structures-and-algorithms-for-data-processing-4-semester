#include "UserInterface.h"


unsigned char UserInterface::GetChek(const char * message, unsigned char maxAccess, FILE * fpIN/* = stdin*/, FILE * fpOUT/* = stdout*/)
{
	unsigned char buffer = ~(unsigned char)0u;
	if (fpIN == NULL) return 0;
	while (true)
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

unsigned UserInterface::GetUnsignedInt(const char * message)
{
	unsigned buffer = 0;
	while (true)
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

float UserInterface::GetFloat(const char * message, FILE * fpIN = stdin, FILE * fpOUT = stdout)
{
	if (fpIN == NULL) return 0.0f;
	float buffer = 0;
	while (true)
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

size_t UserInterface::GetStr(const char * message, char * To, size_t countTo, FILE * fpIN, FILE * fpOUT)
{
	if (fpIN == NULL) return 0u;
	if (fpOUT != NULL) fprintf(fpOUT, "%s Use CTRL + 2 or CTRL + A, CTRL + B, CTRL + D for end.\n", message);
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

signed UserInterface::GetInt(const char * message, FILE * fpIN, FILE * fpOUT)
{
	if (fpIN == NULL) return 0;
	int buffer = 0;
	while (true)
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

unsigned UserInterface::GetUnsignedInt(const char * message, unsigned min, unsigned max)
{
	if (min > max) return min;
	unsigned buffer;
	do
	{
		buffer = GetUnsignedInt(message);
	} while (buffer < min || buffer > max);
	return buffer;
}

void UserInterface::pause(const char * message, FILE * fpOUT, FILE * fpIN)
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
