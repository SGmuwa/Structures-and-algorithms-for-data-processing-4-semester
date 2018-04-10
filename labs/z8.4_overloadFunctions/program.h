#pragma once

#ifndef _INC_PROGRAM_
#define _INC_PROGRAM_

#ifndef _INC_LOCALE
#include <locale.h>
#endif

#ifndef _INC_MATRIX_
#include "matrix.h"
#endif

#ifndef _INC_USERINTERFACE_
#include "UserInterface.h"
#endif

#ifndef _INC_SORTMATRIX_
#include "SortMatrix.h"
#endif

#ifndef _INC_MATRIX_WRITER_
#include "MatrixIO.h"
#endif //!_INC_MATRIX_WRITER_


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

	private:
		unsigned Test_ParseToStringInt();
		unsigned Test_SortMatrixInt();
		unsigned Test_SortMatrixString();

	};
}

#endif // !_INC_PROGRAM_