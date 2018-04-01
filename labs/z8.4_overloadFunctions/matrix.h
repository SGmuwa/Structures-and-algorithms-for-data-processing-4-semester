/*
 * matrix.h
 */

#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <iostream>

template <typename T>
class Matrix {
    public:
        Matrix<T>(size_t r, size_t c);
        Matrix<T>();
        ~Matrix<T>();
        Matrix<T>(const Matrix<T>&);
        Matrix<T>& operator=(const Matrix<T>&);

        inline T& operator()(size_t r, size_t c) { return p[r][c]; }
        

        void swapRows(size_t, size_t);
        Matrix<T> transpose();

        Matrix<T> inverse();

		// Получить количество строк.
		size_t inline getRows();
		// Получить количество столбцов.
		size_t inline getCols();

    private:
        size_t rows_, cols_;
        T **p;

        void allocSpace();
};

#endif
