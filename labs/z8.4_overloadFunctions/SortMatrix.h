#pragma once
#ifndef _INC_SORTMATRIX_
#define _INC_SORTMATRIX_

#ifndef _INC_ARRAY_
#include "Array.h"
#endif


#ifndef _INC_MATRIX_
#include "matrix.h"
#endif

#ifndef _INC_STDIO
#include <stdio.h>
#endif


namespace z8_4
{
	class SortMatrix
	{
	public:
		// Сортировка по следующему правилу:
		// Упорядочить столбцы по убыванию первых элементов столбцов
		// Matrix<int> input: входна¤ матрица, которую следует отсортировать.
		// FILE * fpOUT = NULL: Куда отправить отчёт о каждом шаге сортировки? Укажите NULL, если не надо никуда отправлять.
		static void Sort_by_z8_4(Matrix<int> * input, FILE * fpOUT = NULL);

		// Сортировка по следующему правилу:
		// Упорядочить столбцы по убыванию первых элементов столбцов
		// Matrix<Array<char>> input: входна¤ матрица, которую следует отсортировать.
		// FILE * fpOUT = NULL: Куда отправить отчёт о каждом шаге сортировки? Укажите NULL, если не надо никуда отправлять.
		static void Sort_by_z8_4(Matrix<const Array<char>*> * input, FILE * fpOUT = NULL);
	private:
		template<typename T>
		static void Swap(T & a, T & b);
	};
}
#endif //!_INC_SORTMATRIX_
