﻿#include "SortMatrix.h"

#ifndef _INC_STRING
#include <string.h>
#endif

#ifndef _INC_MATRIX_WRITER_
#include "MatrixIO.h"
#endif
#ifndef _INC_STDIO
#include <stdio.h>
#endif

void z8_4::SortMatrix::Sort_by_z8_4(Matrix<int> * input, FILE * fpOUT)
{
	if (input == NULL) return;
	if (fpOUT != NULL)
	{
		z8_4::MatrixIO::print(input, stdout);
		printf("\n");
	}
	for (size_t i = 0; i < input[0].getCols(); i++)
		for (size_t j = i + 1; j < input[0].getCols(); j++)
			if (input[0](0, i) < input[0](0, j))
			{
				SwapCols(input, i, j);
				if (fpOUT != NULL)
				{
					z8_4::MatrixIO::print(input, stdout);
					printf("\n");
				}
			}

}

void z8_4::SortMatrix::Sort_by_z8_4(Matrix<const Array<char>*> * input, FILE * fpOUT)
{
	if (input == NULL) return;
	if (fpOUT != NULL)
	{
		z8_4::MatrixIO::print(input, stdout);
		printf("\n");
	}
	for (size_t i = 0; i < input[0].getCols(); i++)
		for (size_t j = i + 1; j < input[0].getCols(); j++)
			if (strcmp((char*)input[0](0, i)[0], (char*)input[0](0, j)[0]) < 0)
			{
				SwapCols(input, i, j);
				if (fpOUT != NULL)
				{
					z8_4::MatrixIO::print(input, stdout);
					printf("\n");
				}
			}
}


template<typename T>
void z8_4::SortMatrix::Swap(T & a, T & b)
{
	T buffer = a;
	a = b;
	b = buffer;
	
	//a = a + b;
	//b = a - b;
	//a = a - b;
}

template<typename T>
void z8_4::SortMatrix::SwapCols(Matrix<T> * a, size_t c1, size_t c2)
{
	if (
		a == NULL ||
		c1 == c2 ||
		c1 >= a->getCols() ||
		c2 >= a->getCols() ||
		a->getRows() == 0
		) return;
	for (size_t r = a->getRows() - 1; r != ~(size_t)0; r--)
		Swap((*a)(r, c1), (*a)(r, c2));
}