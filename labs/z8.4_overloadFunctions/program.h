#pragma once

#ifndef _INC_PROGRAM_
#define _INC_PROGRAM_

#ifndef _INC_LOCALE
#include <locale.h>
#endif

#ifndef _INC_STRING
#include <string.h>
#endif // !_INC_STRING

#ifndef _INC_MATRIX_
#include "matrix.h"
#endif

#ifndef _INC_USERINTERFACE_
#include "UserInterface.h"
#endif

#ifndef _INC_Z8_4_TEST_USERINRERFACE
#include "z8.4 test UserInterface.h"
#endif

#ifndef _INC_SORTMATRIX_
#include "SortMatrix.h"
#endif

namespace z8_4
{
	class program
	{
	public:

		program();

		// Выполняется при запуске программы.
		// int argc: количество аргументов командной строки.
		// char * argv[]: указатель на массив строк командной строки.
		// Возвращает: код ошибки.
		int main(int argc, char * argv[]);

		unsigned StartTest();
		template <typename T>
		void GetStarterSizeMatrix(Matrix<T> * in);

	private:
		unsigned Test_ParseToString();
		unsigned Test_SortMatrixInt();
		unsigned Test_SortMatrixString();
		void GetStarterMatrix(Matrix<int> & in);
		void GetStarterMatrix(Matrix<Array<char>> & in);

	};
}

#endif // !_INC_PROGRAM_