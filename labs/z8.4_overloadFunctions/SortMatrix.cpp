#include "SortMatrix.h"

#ifndef _INC_STRING
#include <string.h>
#endif

void z8_4::SortMatrix::Sort_by_z8_4(Matrix<int> * input)
{
	for (size_t i = 0; i < input[0].getCols(); i++)
		for (size_t j = i + 1; j < input[0].getCols(); j++)
			if (input[0](0, i) < input[0](0, j))
				Swap(input[0](0, i), input[0](0, j));
}

void z8_4::SortMatrix::Sort_by_z8_4(Matrix<Array<char>> * input)
{
	for (size_t i = 0; i < input[0].getCols(); i++)
		for (size_t j = i + 1; j < input[0].getCols(); j++)
			if (strcmp((char*)input[0](0, i), (char*)input[0](0, j)) < 0)
				Swap(input[0](0, i), input[0](0, j));
}


template<typename T>
void z8_4::SortMatrix::Swap(T & a, T & b)
{
	T buffer = a;
	a = b;
	b = buffer;
	/*
	a = a + b;
	b = a - b;
	a = a - b;*/
}