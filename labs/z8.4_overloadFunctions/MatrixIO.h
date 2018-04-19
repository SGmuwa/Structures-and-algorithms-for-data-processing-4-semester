#pragma once

#ifndef _INC_MATRIX_WRITER_
#define _INC_MATRIX_WRITER_

#ifndef _INC_MATRIX_
#include "matrix.h"
#endif //!_INC_MATRIX_

#ifndef _INC_STDIO
#include <stdio.h>
#endif //!_INC_STDIO

#ifndef _INC_USERINTERFACE_
#include "UserInterface.h"
#endif //!_INC_USERINTERFACE_

namespace z8_4
{
	class MatrixIO
	{
	public:
		// Отображает матрицу в виде текста.
		// char * to: указатель на место отправления текстовой информации.
		// size_t limit: размер доступной информации.
		// Возвращает: Количество символов записанных в to.
		static size_t toString(const Matrix<const Array<char>*> * input, char * to, size_t limit);

		// Отображает матрицу в виде текста.
		// char * to: указатель на место отправления текстовой информации.
		// size_t limit: размер доступной информации.
		// Возвращает: Количество символов записанных в to.
		static size_t toString(const Matrix<int> * input, char * to, size_t limit);
		// К сожалению, разработка Parse для String затянется на долго. Поэтому я пропущу это.

		// Возвращает: количество символов, которое понадобится для отображения матрицы в текстовый вид.
		static size_t getCountForToString(const Matrix<int> * input);

		// Возвращает: количество символов, которое понадобится для отображения матрицы в текстовый вид.
		static size_t getCountForToString(const Matrix<const Array<char>*> * input);

		// Считывает матрицу из текстового вида.
		// char * from: участок памяти, откуда надо считывать текстовую информацию.
		// Возвращает: экземпляр матрицы, прочитанный из текстового вида.
		static Matrix<int> * parseInt(char * from);

		static Matrix<int> * parseInt(FILE * from, FILE * questions);

		static size_t print(const Matrix<const Array<char>*> * input, FILE * toWriter);

		static size_t print(const Matrix<int> * input, FILE * toWriter);

		template <typename T>
		static Matrix<T> * GetStarterSizeMatrix()
		{
			return new Matrix<T>(
				UserInterface::GetUnsignedInt("Введите количество строк в матрице: ", 1, ~0u),
				UserInterface::GetUnsignedInt("Введите количество стобцов в матрице: ", 1, ~0u)
				);
		}


		static void GetStarterMatrix(Matrix<int> *& output, FILE * fpIN = stdin, FILE * fpOUT = stdout)
		{
			char buffer[1024];
			output = GetStarterSizeMatrix<int>();
			for (size_t i = 0; i < output->getRows(); i++)
				for (size_t j = 0; j < output->getCols(); j++)
				{
#ifndef _MSC_VER
					sprintf(buffer, "Введите целое число для [%lu строки, %lu столбца]", (unsigned long)i, (unsigned long)j);
#else			
					sprintf_s(buffer, sizeof(buffer), "Введите целое число для [%lu строки, %lu столбца]", (unsigned long)i, (unsigned long)j);
#endif
					(*output)(i, j) = UserInterface::GetInt(buffer, fpIN, fpOUT);
				}
		}

		static void GetStarterMatrix(Matrix<const Array<char>*> *& output, FILE * fpIN = stdin, FILE * fpOUT = stdout)
		{
			char bufferToPrint[128];
			char toSave[1024 * 16];
			output = GetStarterSizeMatrix<const Array<char>*>();
			for (size_t i = 0; i < output->getRows(); i++)
				for (size_t j = 0; j < output->getCols(); j++)
				{
#ifndef _MSC_VER
					sprintf(bufferToPrint, "Введите текст для [%lu строки, %lu столбца]\n", (unsigned long)i, (unsigned long)j);
#else
					sprintf_s(bufferToPrint, sizeof(bufferToPrint), "Введите текст для [%lu строки, %lu столбца]\n", (unsigned long)i, (unsigned long)j);
#endif
					output[0](i, j) =
						Array<char>::CreateCopyArray( // Тот массив, который следует поместить в матрицу.
							toSave, // Передаём указатель, показывая, сколько 
							UserInterface::GetStr(bufferToPrint, toSave, sizeof(toSave), fpIN, fpOUT) // Помещаем в buffer информацию, узнавая количество символов
							);
				}
		}

		static void FreeMatrixContent(Matrix<const Array<char>*> * input)
		{
			for (size_t r = input->getRows() - 1; r != ~(size_t)0; r--)
				for (size_t c = input->getCols() - 1; c != ~(size_t)0; c--)
					delete (*input)(r, c);
		}

	};
}

#endif //!_INC_MATRIX_WRITER_