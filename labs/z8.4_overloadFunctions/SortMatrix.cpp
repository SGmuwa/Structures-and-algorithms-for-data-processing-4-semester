#include "SortMatrix.h"

#ifndef _INC_STRING
#include <string.h>
#endif

#if _DEBUG == 1
#ifndef _INC_MATRIX_WRITER_
#include "MatrixIO.h"
#endif
#ifndef _INC_STDIO
#include <stdio.h>
#endif
#endif

void z8_4::SortMatrix::Sort_by_z8_4(Matrix<int> * input)
{
#if _DEBUG == 1
	z8_4::MatrixIO::print((const Matrix<const int>*)input, stdout);
	printf("\n");
#endif
	for (size_t i = 0; i < input[0].getCols(); i++)
		for (size_t j = i + 1; j < input[0].getCols(); j++)
			if (input[0](0, i) < input[0](0, j))
			{
				Swap(input[0](0, i), input[0](0, j));
#if _DEBUG == 1
				z8_4::MatrixIO::print((const Matrix<const int>*)input, stdout);
				printf("\n");
#endif
			}

}

void z8_4::SortMatrix::Sort_by_z8_4(Matrix<Array<char>*> * input)
{
#if _DEBUG == 1
	z8_4::MatrixIO::print((const Matrix<const Array<char>*>*)input, stdout);
	printf("\n");
#endif
	for (size_t i = 0; i < input[0].getCols(); i++)
		for (size_t j = i + 1; j < input[0].getCols(); j++)
			if (strcmp((char*)input[0](0, i), (char*)input[0](0, j)) < 0)
			{
				Swap(input[0](0, i), input[0](0, j));
#if _DEBUG == 1
				z8_4::MatrixIO::print((const Matrix<const Array<char>*>*)input, stdout);
				printf("\n");
#endif
			}
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