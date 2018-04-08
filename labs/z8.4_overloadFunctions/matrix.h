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
	private:
		size_t rows_, cols_;
		T **p;

		void allocSpace()
		{
			p = new T*[rows_];
			for (size_t i = 0; i < rows_; ++i) {
				p[i] = new T[cols_];
			}
		}

	public:
		// Создаёт экземпляр матрицы.
		// size_t rows: количество строк в матрице.
		// size_t cols: количество столбцов в матрице.
		Matrix(size_t rows, size_t cols)
			: rows_(rows), cols_(cols)
		{
			allocSpace();
			for (size_t i = 0; i < rows_; ++i) {
				for (size_t j = 0; j < cols_; ++j) {
					p[i][j] = T();
				}
			}
		}
		Matrix();

		~Matrix()
		{
			for (size_t i = 0; i < rows_; ++i) {
				delete[] p[i];
			}
			delete[] p;
		}

		Matrix(const Matrix<T>& m) : rows_(m.rows_), cols_(m.cols_)
		{
			//allocSpace();
			p = m.p;
			/*for (size_t i = 0; i < rows_; ++i) {
				for (size_t j = 0; j < cols_; ++j) {
					p[i][j];// = m.p[i][j];
				}
			}*/
		}
		//Matrix<T>& operator=(const Matrix<T>&);

		//inline T& operator()(size_t r, size_t c) { return p[r][c]; }
		inline T & operator()(size_t r, size_t c) const 
		{ 
			return (p[r][c]);
		}


		void swapRows(size_t, size_t);
		Matrix<T> transpose();

		Matrix<T> augment(Matrix<T> A, Matrix<T> B);

		// Получить количество строк.
		const size_t inline getRows() const
		{
			return rows_;
		}

		// Получить количество столбцов.
		const size_t inline getCols() const
		{
			return cols_;
		}

		inline operator Matrix<const T>() const
		{
			struct
			{
				size_t rows_, cols_;
				const T ** p;
			} a;
			a.cols_ = cols_;
			a.rows_ = rows_;
			a.p = (const T**)p;
			return *(Matrix<const T> *)(void*)&a;
		}
	};
}
#endif // !_INC_MATRIX_
