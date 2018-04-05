#pragma once
/*
 * matrix.h
 */

#ifndef _INC_MATRIX_
#define _INC_MATRIX_

#ifndef _INC_ARRAY_
#include "Array.h"
#endif


//#include <iostream>
namespace z8_4
{
	template <typename T>
	class Matrix {
	public:
		// Создаёт экземпляр матрицы.
		// size_t rows: количество строк в матрице.
		// size_t cols: количество столбцов в матрице.
		// bool IsNeedDelete = false: True, чтобы при ~Matrix() вызвать ~T(); для каждого элемента. Если вызывать ~T(); для каждого элемента не нужно, оставить False.
		Matrix(size_t rows, size_t cols, bool IsNeedDelete);
		Matrix(size_t rows, size_t cols);
		Matrix();
		~Matrix();
		Matrix(const Matrix<T>&);
		//Matrix<T>& operator=(const Matrix<T>&);

		inline T& operator()(size_t r, size_t c) { return p[r][c]; }


		void swapRows(size_t, size_t);
		Matrix<T> transpose();

		Matrix<T> augment(Matrix<T> A, Matrix<T> B);

		Matrix<T> inverse();

		// Получить количество строк.
		size_t inline getRows();
		// Получить количество столбцов.
		size_t inline getCols();



	private:
		size_t rows_, cols_;
		T **p;
		bool isNeedDelete;

		void allocSpace();
	};
}
#endif // !_INC_MATRIX_
