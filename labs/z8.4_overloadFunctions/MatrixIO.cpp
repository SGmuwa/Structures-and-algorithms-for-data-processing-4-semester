#include "MatrixIO.h"

#ifndef _INC_STRING_
#include <string.h>
#endif //!_INC_STRING_

#ifndef _INC_STDIO
#include <stdio.h>
#include "MatrixIO.h"
#endif //!_INC_STDIO

#ifndef _INC_USERINTERFACE_
#include "UserInterface.h"
#endif

#ifndef _INC_STDLIB
#include <stdlib.h>
#endif

using namespace z8_4;

size_t MatrixIO::toString(const Matrix<const Array<char>*> * input, char * to, size_t limit)
{
#ifdef _MSC_VER
	sprintf_s(to, limit, "{ ");
#else
	sprintf(to, "{ ");
#endif
	for (size_t r = 0; r < input[0].getRows(); r++)
	{
#ifdef _MSC_VER
		sprintf_s(to, limit, "%s{ ", to);
#else
		sprintf(to, "%s{ ", to);
#endif
		for (size_t c = 0; c < input[0].getCols(); c++)
		{
			if (c + 1 < input[0].getCols())
#ifdef _MSC_VER
				sprintf_s(to, limit, "%s%s, ", to, (char*)input[0](r, c)[0]);
			else sprintf_s(to, limit, "%s%s ", to, (char*)input[0](r, c)[0]);
#else
				sprintf(to, "%s%s, ", to, (char*)input[0](r, c)[0]);
			else sprintf(to, "%s%s ", to, (char*)input[0](r, c)[0]);
#endif
		}
		if (r + 1 < input[0].getRows())
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
	return (size_t)
#ifdef _MSC_VER
		sprintf_s(to, limit, "%s}", to)
#else
		sprintf(to, "%s}", to)
#endif
		+ 1u;
}

size_t MatrixIO::toString(const Matrix<const int> * input, char * to, size_t limit)
{

#ifdef _MSC_VER
	sprintf_s(to, limit, "{ ");
#else
	sprintf(to, "{ ");
#endif
	for (size_t r = 0; r < input[0].getRows(); r++)
	{
#ifdef _MSC_VER
		sprintf_s(to, limit, "%s{", to);
#else
		sprintf(to, "%s{", to);
#endif
		for (size_t c = 0; c < input[0].getCols(); c++)
		{
			if (c + 1 < input[0].getCols())
#ifdef _MSC_VER
				sprintf_s(to, limit, "%s%d, ", to, input[0](r, c));
#else
				sprintf(to, "%s%d, ", to, input(r, c));
#endif
			else
#ifdef _MSC_VER
				sprintf_s(to, limit, "%s%d", to, input[0](r, c));
#else
				sprintf(to, "%s%d", to, input[0](r, c));
#endif
		}
		if (r + 1 < input[0].getRows())
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
	return (size_t)
#ifdef _MSC_VER
		sprintf_s(to, limit, "%s}", to)
#else
		sprintf(to, "%s}", to)
#endif
		+ 1u;
}

size_t MatrixIO::getCountForToString(const Matrix<const Array<char>*> * input)
{
	size_t output = 0u;
	output += 3;
	for (size_t r = 0; r < input[0].getRows(); r++)
	{
		output += 2;
		for (size_t c = 0; c < input[0].getCols(); c++)
		{
			if (c + 1 < input[0].getCols())
				output += strlen((const char*)input[0](r, c)) + 2;
			else output += strlen((const char*)input[0](r, c)) + 1;
		}
		if (r + 1 < input[0].getRows())
			output += 3;
		else
			output += 2;
	}
	return ++output;
}

size_t MatrixIO::getCountForToString(const Matrix<const int> * input)
{
	size_t output = 0;
	char buffer[64] = { 0 };
	output += 3;
	for (size_t r = 0; r < input[0].getRows(); r++)
	{
		output += 1;
		for (size_t c = 0; c < input[0].getCols(); c++)
		{
			if (c + 1 < input[0].getCols())
#ifdef _MSC_VER
				sprintf_s(buffer, sizeof(buffer) / sizeof(char), "%d, ", input[0](r, c));
#else
				sprintf(buffer, "%d, ", input[0](r, c));
#endif
			else
#ifdef _MSC_VER
				sprintf_s(buffer, sizeof(buffer) / sizeof(char), "%d", input[0](r, c));
#else
				sprintf(buffer, "%d ", input[0](r, c));
#endif
			output += strlen(buffer);
		}
		if (r + 1 < input[0].getRows())
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


Matrix<int> * MatrixIO::parseInt(char * from)
{
	char * start = from;
	size_t countStart = 0; // Считает количество символов '{'.
	size_t getCountDigit = 0; // Считает количество цифр в from.
	bool isThisNumber_getCountDigit = false; // Используется для getCountDigit как флаг. True - если предыдущий символ является цифрой. Иначе - false.
	size_t countEnd = 0; // Считает количество символов '}'.
	for (; countStart - 1 >= countEnd || countEnd == 0; from++)
	{
		if (*from >= '0' && *from <= '9')
		{
			if (isThisNumber_getCountDigit == false) // Если предыдущий символ был не число, то
				getCountDigit++;
			isThisNumber_getCountDigit = true;
		}
		else
		{
			isThisNumber_getCountDigit = false;
			if (*from == '{')
			{
				countStart++;
			}
			else if (*from == '}')
			{
				countEnd++;
			}
			else if (*from == '\0') return nullptr;
		}
	}
	Matrix<int> * output = new Matrix<int>(countStart - 1, getCountDigit / (countStart - 1));
	from = start;
	size_t r = 0;
	size_t c = 0;
	if (r < output->getRows() && c < output->getCols())
		for (; *from != '\0'; from++)
		{
			if (*from >= '0' && *from <= '9')
			{
#ifndef _MSC_VER
				sscanf(from, "%d", &(*output)(r, c)); // Считываем это число
#else
				sscanf_s(from, "%d", &(*output)(r, c));
#endif
				c++;
				if (c >= output->getCols())
				{
					c = 0;
					r++;
					if (r >= output->getRows())
					{
						break;
					}
				}
				for (; (*from >= '0' && *from <= '9') == false; from++); // Пропускаем это число
			}
		}
	return output;
}

Matrix<int> * MatrixIO::parseInt(FILE * from, FILE * questions)
{
	size_t NumberOfAttempts = 0u;
	Matrix<int> * output = NULL;
	if (from == NULL) return NULL;
	char * buffer = new char[1024 * 4 * 10]; // 40 килобайт текстовой информации!
	do
	{
		UserInterface::GetStr("Input Matrix. Example: { {1, 2, 3}, {4, 5, 6}, {7, 8, 9}}\n", buffer, 1024 * 40, from, questions);
		output = parseInt(buffer);
	} while (output == NULL);
	return output;
}



size_t MatrixIO::print(const Matrix<const Array<char>*> * input, FILE * toWriter)
{
	size_t sizeBuffer = getCountForToString(input);
	char * buffer = new char[sizeBuffer];
	toString(input, buffer, sizeBuffer);
	size_t output = fwrite(buffer, sizeof(char), sizeBuffer / sizeof(char), toWriter);
	delete[] buffer; return output;
}

size_t MatrixIO::print(const Matrix<const int> * input, FILE * toWriter)
{
	size_t sizeBuffer = getCountForToString(input);
	char * buffer = new char[sizeBuffer];
	toString(input, buffer, sizeBuffer);
	size_t output = fwrite(buffer, sizeof(char), sizeBuffer / sizeof(char), toWriter);
	delete[] buffer; return output;
}
