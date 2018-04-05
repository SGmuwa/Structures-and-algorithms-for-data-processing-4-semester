/*
 * matrix.cpp
 */

//#include <stdexcept>
#include "matrix.h"


#ifndef _INC_STDIO
#include <stdio.h>
#endif // !_INC_STDIO

//#define EPS 1e-10

//using std::ostream;  using std::istream;  using std::endl;
//using std::domain_error;

/* PUBLIC MEMBER FUNCTIONS
 ********************************/

template <typename T>
z8_4::Matrix<T>::Matrix(size_t rows, size_t cols, bool IsNeedDelete)
	: rows_(rows), cols_(cols), isNeedDelete(IsNeedDelete)
{
    allocSpace();
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            p[i][j] = T();
        }
    }
}

template <typename T>
z8_4::Matrix<T>::Matrix(size_t rows, size_t cols)
	: rows_(rows), cols_(cols), isNeedDelete(false)
{
	allocSpace();
	for (size_t i = 0; i < rows_; ++i) {
		for (size_t j = 0; j < cols_; ++j) {
			p[i][j] = T();
		}
	}
}

template <typename T>
z8_4::Matrix<T>::Matrix() : rows_(1), cols_(1), isNeedDelete(false)
{
    allocSpace();
    p[0][0] = 0;
}

template <typename T>
z8_4::Matrix<T>::~Matrix()
{
    for (size_t i = 0; i < rows_; ++i) {
		if(isNeedDelete)
			for (size_t j = 0; j < cols_; j++)
			{
				//delete p[i][j];
				// p[i][j].~T();
			}
        delete[] p[i];
    }
    delete[] p;
}

template <typename T>
z8_4::Matrix<T>::Matrix(const Matrix<T>& m) : rows_(m.rows_), cols_(m.cols_)
{
    allocSpace();
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            p[i][j] = m.p[i][j];
        }
    }
}

/*
// Я не знаю, как очистить тогда память у отработанного const Matrix& m, поэтому я закомментирую данный оператор
template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& m)
{
    if (this == &m) {
        return *this;
    }

    if (rows_ != m.rows_ || cols_ != m.cols_) {
        for (size_t i = 0; i < rows_; ++i) {
            delete[] p[i];
        }
        delete[] p;

        rows_ = m.rows_;
        cols_ = m.cols_;
        allocSpace();
    }

    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            p[i][j] = m.p[i][j];
        }
    }
    return *this;
}
*/

template <typename T>
void z8_4::Matrix<T>::swapRows(size_t r1, size_t r2)
{
    T *temp = p[r1];
    p[r1] = p[r2];
    p[r2] = temp;
}

template <typename T>
z8_4::Matrix<T> z8_4::Matrix<T>::transpose()
{
    Matrix<T> ret(cols_, rows_);
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            ret.p[j][i] = p[i][j];
        }
    }
    return ret;
}


/* STATIC CLASS FUNCTIONS
 ********************************/


// functions on AUGMENTED matrices
template <typename T>
z8_4::Matrix<T> z8_4::Matrix<T>::augment(Matrix<T> A, Matrix<T> B)
{
    Matrix AB(A.rows_, A.cols_ + B.cols_);
    for (size_t i = 0; i < AB.rows_; ++i) {
        for (size_t j = 0; j < AB.cols_; ++j) {
            if (j < A.cols_)
                AB(i, j) = A(i, j);
            else
                AB(i, j) = B(i, j - B.cols_);
        }
    }
    return AB;
}

template <typename T>
z8_4::Matrix<T> z8_4::Matrix<T>::inverse()
{
    Matrix<T> I = Matrix<T>::createIdentity(rows_);
    Matrix<T> AI = Matrix<T>::augment(*this, I);
    Matrix<T> U = AI.gaussianEliminate();
    Matrix<T> IAInverse = U.rowReduceFromGaussian();
    Matrix<T> AInverse(rows_, cols_);
    for (size_t i = 0; i < AInverse.rows_; ++i) {
        for (size_t j = 0; j < AInverse.cols_; ++j) {
            AInverse(i, j) = IAInverse(i, j + cols_);
        }
    }
    return AInverse;
}

template<typename T>
size_t inline z8_4::Matrix<T>::getRows()
{
	return cols_;
}

template<typename T>
size_t inline z8_4::Matrix<T>::getCols()
{
	return cols_;
}



/* PRIVATE HELPER FUNCTIONS
 ********************************/

template <typename T>
void z8_4::Matrix<T>::allocSpace()
{
    p = new T*[rows_];
    for (size_t i = 0; i < rows_; ++i) {
        p[i] = new T[cols_];
    }
}
