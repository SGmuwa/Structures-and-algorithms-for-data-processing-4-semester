#pragma once
#include "Array.h"
namespace z8_4
{
	static class program
	{
	public:
		// Выполняется при запуске программы.
		// int argc: количество аргументов командной строки.
		// char * argv[]: указатель на массив строк командной строки.
		// Возвращает: код ошибки.
		static int main(int argc, char * argv[]);
		template <typename T>
		static void GetStarterSizeMatrix(Matrix<T>& in);
		static void GetStarterMatrix(Matrix<int> & in);
		static void GetStarterMatrix(Matrix<Array<char>> & in);

	};
}
