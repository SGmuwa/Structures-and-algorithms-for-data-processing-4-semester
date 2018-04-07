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
z8_4::Matrix<T>::Matrix() : rows_(1), cols_(1)
{
    allocSpace();
    p[0][0] = 0;
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





/* PRIVATE HELPER FUNCTIONS
 ********************************/


