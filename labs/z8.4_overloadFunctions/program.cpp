#include "program.h"
#include "UserInterface.h"
#include <locale.h>
#include "matrix.h"
int z8_4::program::main(int argc, char * argv[])
{
	setlocale(LC_ALL, "Russian");
	switch (UserInterface::GetChek("С каким типом данных вы будете работать?\n0. Целые числа\n1. Текст", 1))
	{
	case 0:
		break;
	default:

	}
	return 0;
}

template <typename T>
void z8_4::program::GetStarterSizeMatrix(Matrix<T> & in)
{
	in = Matrix<T>(
		UserInterface::GetUnsignedInt("Введите количество строк в матрице: ", 1, -1u),
		UserInterface::GetUnsignedInt("Введите количество стобцов в матрице: ", 1, -1u)
		);
}

void z8_4::program::GetStarterMatrix(Matrix<int> & in)
{
	char buffer[1024];
	GetStarterSizeMatrix(in);
	for(size_t i = 0; i < in.getRows(); i++)
		for (size_t j = 0; j < in.getCols(); j++)
		{
			sprintf(buffer, "Введите целое число для [%lu строки, %lu столбца]", (unsigned long)i, (unsigned long)j);
			in(i, j) = UserInterface::GetInt(buffer);
		}
}

void z8_4::program::GetStarterMatrix(Matrix<Array<char>> & in)
{
	char bufferToPrint[128];
	char toSave[1024 * 16];
	GetStarterSizeMatrix(in);
	for (size_t i = 0; i < in.getRows(); i++)
		for (size_t j = 0; j < in.getCols(); j++)
		{
			printf(bufferToPrint, "Введите текст для [%lu строки, %lu столбца]\n", (unsigned long)i, (unsigned long)j);
			in(i, j) =
			Array<char>( // Тот массив, который следует поместить в матрицу.
				bufferToPrint, // Передаём указатель, показывая, сколько 
				UserInterface::GetStr(bufferToPrint, toSave, sizeof(toSave), stdin, stdout), // Помещаем в buffer информацию, узнавая количество символов
				true // Да, стереть информацию потом необходимо.
				); 
		}
}

