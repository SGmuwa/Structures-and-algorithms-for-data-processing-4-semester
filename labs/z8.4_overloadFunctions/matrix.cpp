/*
 * matrix.cpp
 */

#include <stdexcept>
#include "matrix.h"

#define EPS 1e-10

using std::ostream;  using std::istream;  using std::endl;
using std::domain_error;

/* PUBLIC MEMBER FUNCTIONS
 ********************************/

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t cols) : rows_(rows), cols_(cols)
{
    allocSpace();
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            p[i][j] = 0;
        }
    }
}

template <typename T>
Matrix<T>::Matrix() : rows_(1), cols_(1)
{
    allocSpace();
    p[0][0] = 0;
}

template <typename T>
Matrix<T>::~Matrix()
{
    for (size_t i = 0; i < rows_; ++i) {
        delete[] p[i];
    }
    delete[] p;
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& m) : rows_(m.rows_), cols_(m.cols_)
{
    allocSpace();
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            p[i][j] = m.p[i][j];
        }
    }
}

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

template <typename T>
void Matrix<T>::swapRows(size_t r1, size_t r2)
{
    T *temp = p[r1];
    p[r1] = p[r2];
    p[r2] = temp;
}

template <typename T>
Matrix<T> Matrix<T>::transpose()
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
Matrix<T> Matrix<T>::augment(Matrix<T> A, Matrix<T> B)
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
Matrix<T> Matrix<T>::inverse()
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
size_t inline Matrix<T>::getRows()
{
	return cols_;
}

template<typename T>
size_t inline Matrix<T>::getCols()
{
	return cols_;
}


/* PRIVATE HELPER FUNCTIONS
 ********************************/

template <typename T>
void Matrix<T>::allocSpace()
{
    p = new T*[rows_];
    for (size_t i = 0; i < rows_; ++i) {
        p[i] = new T[cols_];
    }
}
