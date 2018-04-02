#pragma once
#ifndef _INC_SORTMATRIX_
#define _INC_SORTMATRIX_

#ifndef _INC_ARRAY_
#include "Array.h"
#endif


#ifndef _INC_MATRIX_
#include "matrix.h"
#endif

namespace z8_4
{
	class SortMatrix
	{
	public:
		// Сортировка по следующему правилу:
		// Упорядочить столбцы по убыванию первых элементов столбцов
		// Matrix<int> input: входная матрица, которую следует отсортировать.
		static void Sort_by_z8_4(Matrix<int> input);

		// Сортировка по следующему правилу:
		// Упорядочить столбцы по убыванию первых элементов столбцов
		// Matrix<Array<char>> input: входная матрица, которую следует отсортировать.
		static void Sort_by_z8_4(Matrix<Array<char>> input);
	private:
		template<typename T>
		static void Swap(T & a, T & b);
	};
}
#endif //!_INC_SORTMATRIX_
