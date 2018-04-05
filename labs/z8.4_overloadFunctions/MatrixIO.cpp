﻿#include "MatrixIO.h"

#ifndef _INC_STRING_
#include <string.h>
#endif //!_INC_STRING_

#ifndef _INC_STDIO
#include <stdio.h>
#include "MatrixIO.h"
#endif //!_INC_STDIO

bool z8_4::MatrixIO::toString(Matrix<Array<char>> input, char * to, size_t limit)
{
#ifdef _MSC_VER
	sprintf_s(to, limit, "{ ");
#else
	sprintf(to, "{ ");
#endif
	for (size_t r = 0; r < input.getRows(); r++)
	{
#ifdef _MSC_VER
		sprintf_s(to, limit, "%s{ ", to);
#else
		sprintf(to, "%s{ ", to);
#endif
		for (size_t c = 0; c < input.getCols(); c++)
		{
			if (c + 1 < input.getCols())
#ifdef _MSC_VER
				sprintf_s(to, limit, "%s%s, ", to, (char*)input(r, c));
			else sprintf_s(to, limit, "%s%s ", to, (char*)input(r, c));
#else
				sprintf(to, "%s%s, ", to, (char*)input(r, c));
			else sprintf(to, "%s%s ", to, (char*)input(r, c));
#endif
		}
		if (r + 1 < input.getRows())
#ifdef _MSC_VER
			sprintf_s(to, limit, "%s}, ", to);
#else
			sprintf(to, "%s}, ", to);
#endif
		else
#ifdef _MSC_VER
			sprintf_s(to, limit, "%s} ", to);
#else
			sprintf(to, "%s} ", to);
#endif
	}
#if _DEBUG == 1
	int debug = sprintf_s(to, limit, "%s}", to);
	printf("sprintf_s: %d", debug);
	return ((long)debug < (long)limit);
#else
	return ((long)
#ifdef _MSC_VER
		sprintf_s(to, limit, "%s}", to)
#else
		sprintf(to, "%s}", to)
#endif
		< (long)limit);
#endif
}

bool z8_4::MatrixIO::toString(Matrix<int> input, char * to, size_t limit)
{

#ifdef _MSC_VER
	sprintf_s(to, limit, "{ ");
#else
	sprintf(to, "{ ");
#endif
	for (size_t r = 0; r < input.getRows(); r++)
	{
#ifdef _MSC_VER
		sprintf_s(to, limit, "%s{ ", to);
#else
		sprintf(to, "%s{ ", to);
#endif
		for (size_t c = 0; c < input.getCols(); c++)
		{
			if (c + 1 < input.getCols())
#ifdef _MSC_VER
				sprintf_s(to, limit, "%s%d, ", to, input(r, c));
#else
				sprintf(to, "%s%d, ", to, input(r, c));
#endif
			else
#ifdef _MSC_VER
				sprintf_s(to, limit, "%s%d ", to, input(r, c));
#else
				sprintf(to, "%s%d ", to, input(r, c));
#endif
		}
		if (r + 1 < input.getRows())
#ifdef _MSC_VER
			sprintf_s(to, limit, "%s}, ", to);
#else
			sprintf(to, "%s}, ", to);
#endif
		else
#ifdef _MSC_VER
			sprintf_s(to, limit, "%s} ", to);
#else
			sprintf(to, "%s} ", to);
#endif
	}
	return (long)
#ifdef _MSC_VER
		sprintf_s(to, limit, "%s}", to)
#else
		sprintf(to, "%s}", to)
#endif
		< (long)limit;
}

size_t z8_4::MatrixIO::getCountForToString(Matrix<Array<char>> input)
{
	size_t output = 0u;
	char buffer[64];
	output += 3;
	for (size_t r = 0; r < input.getRows(); r++)
	{
		output += 2;
		for (size_t c = 0; c < input.getCols(); c++)
		{
			if (c + 1 < input.getCols())
				output += strlen((char*)input(r, c)) + 2;
			else output += strlen((char*)input(r, c)) + 1;
		}
		if (r + 1 < input.getRows())
			output += 3;
		else
			output += 2;
	}
	return ++output;
}

size_t z8_4::MatrixIO::getCountForToString(Matrix<int> input)
{
	size_t output = 0;
	char buffer[64] = { 0 };
	output += 3;
	for (size_t r = 0; r < input.getRows(); r++)
	{
		output += 2;
		for (size_t c = 0; c < input.getCols(); c++)
		{
			if (c + 1 < input.getCols())
#ifdef _MSC_VER
				sprintf_s(buffer, sizeof(buffer) / sizeof(char), "%d, ", input(r, c));
#else
				sprintf(buffer, "%d, ", input(r, c));
#endif
			else
#ifdef _MSC_VER
				sprintf_s(buffer, sizeof(buffer) / sizeof(char), "%d ", input(r, c));
#else
				sprintf(buffer, "%d ", input(r, c));
#endif
			output += strlen(buffer);
		}
		if (r + 1 < input.getRows())
			output += 3;
		else
			output += 2;
	}
	return ++output/*(long)
#ifdef _MSC_VER
		sprintf_s(buffer, sizeof(buffer) / sizeof(char), "}")
#else
		sprintf(buffer, "}")
#endif
		< (long)limit*/;
}


z8_4::Matrix<int> z8_4::MatrixIO::parseInt(char * from)
{
	char * start = from;
	size_t countStart = 0; // Считает количество символов '{'.
	size_t getCountDigit = 0; // Считает количество цифр в from.
	bool isThisNumber_getCountDigit = false; // Используется для getCountDigit как флаг. True - если предыдущий символ является цифрой. Иначе - false.
	size_t countEnd = 0; // Считает количество символов '}'.
	for (; countStart == countEnd && countStart != 0; from++)
	{
		if (*from >= '0' && *from <= '9')
		{
			if (isThisNumber_getCountDigit == false) // Если предыдущий символ был не число, то
				getCountDigit++;
			isThisNumber_getCountDigit = true;
		}
		else isThisNumber_getCountDigit = false;
		if (*from == '{')
		{
			countStart++;
		}
		if (*from == '}')
		{
			countEnd++;
		}
		if (*from == '\0') return Matrix<int>();
	}
	Matrix<int> output = Matrix<int>(countStart - 1, getCountDigit / (countStart - 1));
	from = start;
	for (size_t r = 0; r < output.getRows(); r++)
		for (size_t c = 0; c < output.getCols(); c++)
		{
			for (; *from != '\0'; from++)
			{
				if (*from >= '0' && *from <= '9')
				{
#ifndef _MSC_VER
					sscanf(from, "%d", &output(r, c)); // Считываем это число
#else
					sscanf_s(from, "%d", &output(r, c));
#endif
					for (; (*from >= '0' && *from <= '9') == false; from++); // Пропускаем это число
				}
			}
		}
	return output;
}

#define SUPPPPPPPPPEEEEERRRRRR char * buffer = new char[getCountForToString(input)]; toString(input, buffer, sizeof(buffer)); size_t output = fwrite(buffer, sizeof(char), sizeof(buffer) / sizeof(char), toWriter); delete[] buffer; return output;
size_t z8_4::MatrixIO::print(Matrix<Array<char>> input, FILE * toWriter)
{
	SUPPPPPPPPPEEEEERRRRRR
}

size_t z8_4::MatrixIO::print(Matrix<int> input, FILE * toWriter)
{
	SUPPPPPPPPPEEEEERRRRRR
}

#undef SUPPPPPPPPPEEEEERRRRRR
