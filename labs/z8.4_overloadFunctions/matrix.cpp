/*
 * matrix.cpp
 */

//#include <stdexcept>
#include "matrix.h"

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
            p[i][j] = 0;
        }
    }
}

template<typename T>
z8_4::Matrix<T>::Matrix(size_t rows, size_t cols)
	: rows_(rows), cols_(cols), isNeedDelete(false)
{
	allocSpace();
	for (size_t i = 0; i < rows_; ++i) {
		for (size_t j = 0; j < cols_; ++j) {
			p[i][j] = 0;
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
				p[i][j].~T();
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

z8_4::Matrix<int> z8_4::Matrix<int>::parse(char * from)
{
	char * start = from;
	size_t countStart = 0; // Считает количество символов '{'.
	size_t getCountDigit = 0; // Считает количество цифр в from.
	bool isThisNumber_getCountDigit = false; // Используется для getCountDigit как флаг. True - если предыдущий символ является цифрой. Иначе - false.
	size_t countEnd = 0; // Считает количество символов '}'.
	for (; countStart == countEnd && countStart != 0; from++)
	{
		if (*from >= '0' && *from <= '9')
		{
			if (isThisNumber_getCountDigit == false) // Если предыдущий символ был не число, то
				getCountDigit++;
			isThisNumber_getCountDigit = true;
		}
		else isThisNumber_getCountDigit = false;
		if (*from == '{')
		{
			countStart++;
		}
		if (*from == '}')
		{
			countEnd++;
		}
		if (*from == '\0') return Matrix<int>();
	}
	Matrix<int> output = Matrix<int>(countStart - 1, getCountDigit / (countStart - 1));
	from = start;
	for (size_t r = 0; r < output.getRows(); r++)
		for (size_t c = 0; c < output.getCols(); c++)
		{
			for (; *from != '\0'; from++)
			{
				if (*from >= '0' && *from <= '9')
				{
#ifndef _MSC_VER
					sscanf(from, "%d", &output(r, c)); // Считываем это число
#else
					sscanf_s(from, "%d", &output(r, c));
#endif
					for (; (*from >= '0' && *from <= '9') == false; from++); // Пропускаем это число
				}
			}
		}
	return output;
}


bool z8_4::toString(z8_4::Matrix<int> input, char * to, size_t limit)
{
#ifdef _MSC_VER
	sprintf_s(to, limit, "{ ");
#else
	sprintf(to, "{ ");
#endif
	for (size_t r = 0; r < input.getRows(); r++)
	{
#ifdef _MSC_VER
		sprintf_s(to, limit, "%s{ ", to);
#else
		sprintf(to, "%s{ ", to);
#endif
		for (size_t c = 0; c < input.getCols(); c++)
		{
			if (c + 1 < input.getCols()) 
#ifdef _MSC_VER
				sprintf_s(to, limit, "%s%d, ", to, input(r, c));
#else
				sprintf(to, "%s%d, ", to, input(r, c));
#endif
			else
#ifdef _MSC_VER
				sprintf_s(to, limit, "%s%d ", to, input(r, c));
#else
				sprintf(to, "%s%d ", to, input(r, c));
#endif
		}
		if (r + 1 < input.getRows())
#ifdef _MSC_VER
			sprintf_s(to, limit, "%s}, ", to);
#else
			sprintf(to,  "%s}, ", to);
#endif
		else 
#ifdef _MSC_VER
			sprintf_s(to, limit, "%s} ", to);
#else
			sprintf(to, "%s} ", to);
#endif
	}
	return (long)
#ifdef _MSC_VER
		sprintf_s(to, limit, "%s}", to)
#else
		sprintf(to, "%s}", to)
#endif
		< (long)limit;
}


bool z8_4::toString(z8_4::Matrix<z8_4::Array<char>> input, char * to, size_t limit)
{
#ifdef _MSC_VER
	sprintf_s(to, limit, "{ ");
#else
	sprintf(to, "{ ");
#endif
	for (size_t r = 0; r < input.getRows(); r++)
	{
#ifdef _MSC_VER
		sprintf_s(to, limit, "%s{ ", to);
#else
		sprintf(to, "%s{ ", to);
#endif
		for (size_t c = 0; c < input.getCols(); c++)
		{
			if (c + 1 < input.getCols()) 
#ifdef _MSC_VER
				sprintf_s(to, limit, "%s%s, ", to, (char*)input(r, c));
			else sprintf_s(to, limit, "%s%s ", to, (char*)input(r, c));
#else
				sprintf(to, "%s%s, ", to, (char*)input(r, c));
			else sprintf(to, "%s%s ", to, (char*)input(r, c));
#endif
		}
		if (r + 1 < input.getRows())
#ifdef _MSC_VER
			sprintf_s(to, limit, "%s}, ", to);
#else
			sprintf(to, "%s}, ", to);
#endif
		else
#ifdef _MSC_VER
			sprintf_s(to, limit, "%s} ", to);
#else
			sprintf(to, "%s} ", to);
#endif
	}
#if _DEBUG == 1
	int debug = sprintf_s(to, limit, "%s}", to);
	printf("sprintf_s: %d", debug);
	return ((long)debug < (long)limit);
#else
	return ((long)
#ifdef _MSC_VER
		sprintf_s(to, limit, "%s}", to)
#else
		sprintf(to, "%s}", to)
#endif
		< (long)limit);
#endif
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
