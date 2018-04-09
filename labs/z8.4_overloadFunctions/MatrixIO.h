#pragma once

#ifndef _INC_MATRIX_WRITER_
#define _INC_MATRIX_WRITER_

#ifndef _INC_MATRIX_
#include "matrix.h"
#endif

#ifndef _INC_STDIO
#include <stdio.h>
#endif //!_INC_STDIO

namespace z8_4
{
	class MatrixIO
	{
	public:
		// Отображает матрицу в виде текста.
		// char * to: указатель на место отправления текстовой информации.
		// size_t limit: размер доступной информации.
		// Возвращает: True, если объект Matrix<T> поместился полностью. Иначе: False.
		static bool toString(const Matrix<const Array<char>> * input, char * to, size_t limit);

		// Отображает матрицу в виде текста.
		// char * to: указатель на место отправления текстовой информации.
		// size_t limit: размер доступной информации.
		// Возвращает: True, если объект Matrix<T> поместился полностью. Иначе: False.
		static bool toString(const Matrix<const int> * input, char * to, size_t limit);
		// К сожалению, разработка Parse для String затянется на долго. Поэтому я пропущу это.

		// Возвращает: количество символов, которое понадобится для отображения матрицы в текстовый вид.
		static size_t getCountForToString(const Matrix<const int> * input);

		// Возвращает: количество символов, которое понадобится для отображения матрицы в текстовый вид.
		static size_t getCountForToString(const Matrix<const Array<char>> * input);

		// Считывает матрицу из текстового вида.
		// char * from: участок памяти, откуда надо считывать текстовую информацию.
		// Возвращает: экземпляр матрицы, прочитанный из текстового вида.
		static Matrix<int> * parseInt(char * from);

		static Matrix<int> * parseInt(FILE * from, FILE * questions);

		static size_t print(const Matrix<const Array<char>> * input, FILE * toWriter);

		static size_t print(const Matrix<const int> * input, FILE * toWriter);

	};
}

#endif //!_INC_MATRIX_WRITER_