#include "program.h"

#ifndef _INC_Z8_4_TEST_USERINRERFACE
#include "z8.4 test UserInterface.h"
#endif

#ifndef _INC_STRING
#include <string.h>
#endif // !_INC_STRING

int main(int argc, char * argv[]) {  return z8_4::program().main(argc, argv); }

z8_4::program::program() {}

int z8_4::program::main(int argc, char * argv[])
{
	setlocale(LC_ALL, "Russian");
	StartTest();
	switch (UserInterface::GetChek("С каким типом данных вы будете работать?\n0. Целые числа\n1. Текст", 1))
	{
	case 0:
		break;
	default:
		break;
	}

	return 0;
}

unsigned z8_4::program::StartTest()
{
	unsigned errors = 0;
	test_UserInterface::log(true, "\nТестирование началось.\n");
	
	errors += Test_ParseToStringInt();
	errors += Test_SortMatrixInt();
	errors += Test_SortMatrixString();

	test_UserInterface::log(true, "Тестирование окончено. Количество ошибок: ", errors);
	return errors;
}

unsigned z8_4::program::Test_ParseToStringInt()
{
	test_UserInterface::log(true, "\nPARSE-toString START\n");
	unsigned errors = 0;
	Matrix<int> * mat = MatrixIO::parseInt("{ {1, 2, 3}, {4, 5, 6}, {7, 8, 9} }");
	if (mat == NULL)
	{
		test_UserInterface::log(false, "mat is NULL!!! Test end.");
		return ++errors;
	}
	int i = 1;
	for (size_t r = 0; r < mat->getRows(); r++)
		for (size_t c = 0; c < mat->getCols(); c++)
		{
			if (mat[0](r, c) != i)
			{
				test_UserInterface::log(false, "Parse: error. mat(r, c) != i. i = ", i);
				test_UserInterface::log(false, "r = ", r);
				test_UserInterface::log(false, "c = ", c);
				test_UserInterface::log(false, "(*mat)(r, c) = ", (*mat)(r, c));
				errors++;
			}
			else test_UserInterface::log(true, "Parse: mat(r, c) == i. i = ", i);
			i++;
		}
	test_UserInterface::log(true, "Parse end.");
	char MemoryToString[64]; // Участок памяти хранения вывода toString.
	z8_4::MatrixIO::toString((const Matrix<const int>*)mat, MemoryToString, sizeof(MemoryToString));
	test_UserInterface::log(true, MemoryToString);
	if (strcmp(MemoryToString, "{ {1, 2, 3}, {4, 5, 6}, {7, 8, 9} }") != 0)
	{
		test_UserInterface::log(false, "String does not coincide with the expected!");
		errors++;
	}
	else test_UserInterface::log(true, "String does coincide with the expected.");
	delete mat;
	mat = MatrixIO::parseInt(MemoryToString);
	if (mat == NULL)
	{
		test_UserInterface::log(false, "mat is NULL!!! Test end.");
		return ++errors;
	}


	i = 1;
	for (size_t r = 0; r < mat[0].getRows(); r++)
		for (size_t c = 0; c < mat[0].getCols(); c++)
		{
			if (mat[0](r, c) != i)
			{
				test_UserInterface::log(false, "Parse: error. mat(r, c) != i. i = ", i);
				errors++;
			}
			else test_UserInterface::log(true, "Parse: mat(r, c) == i. i = ", i);
			i++;
		}
	test_UserInterface::log(true, "Parse end.");

	MatrixIO::toString((const Matrix<const int>*)mat, MemoryToString, sizeof(MemoryToString));
	test_UserInterface::log(true, MemoryToString);
	if (strcmp(MemoryToString, "{ {1, 2, 3}, {4, 5, 6}, {7, 8, 9} }") != 0)
	{
		test_UserInterface::log(false, "String does not coincide with the expected!");
		errors++;
	}
	else test_UserInterface::log(true, "String does coincide with the expected.");
	delete mat;
	test_UserInterface::log(true, "PARSE-toString END");
	return errors;
}

unsigned z8_4::program::Test_SortMatrixInt()
{
	unsigned errors = 0;
	test_UserInterface::log(true, "\nТестирование сортировки.\n");
	Matrix<int> * mat = new Matrix<int>(3, 3);
	test_UserInterface::log(true, "Экземпляр матрицы создан.");
	int i = 2;
	for (size_t r = 0; r < (*mat).getRows(); r++)
		for (size_t c = 0; c < (*mat).getCols(); c++)
		{
			(*mat)(r, c) = i++;
		}

	SortMatrix::Sort_by_z8_4(mat);

	i = 2;
	for (size_t r = 0; r < (*mat).getRows(); r++)
		for (size_t c = 0; c < (*mat).getCols(); c++)
		{
			if (r != 0)
				if ((*mat)(r, c) != i)
				{
					test_UserInterface::log(false, "Отклонение адресации в сортировке. i = ", i);
					errors++;
				}
				else test_UserInterface::log(true, "Элемент, который не должен был измениться, не изменился. i = ", i);
			i++;
		}
	for (size_t c = 0; c < (*mat).getCols() - 1; c++)
	{
		if (((*mat)(0, c) <= (*mat)(0, c + 1)) == false)
		{
			test_UserInterface::log(false, "К сожалению, матрица не отсортирована. c = ", c);
			errors++;
		}
		else test_UserInterface::log(true, "Элементы отсортированы. c = ", c);
	}
	delete mat;
	test_UserInterface::log(true, "Тестирование сортировки завершено.");
	return errors;
}

unsigned z8_4::program::Test_SortMatrixString()
{
	unsigned errors = 0;
	test_UserInterface::log(true, "\nТестирование сортировки (строки).\n");
	Matrix<Array<char>> * mat = new Matrix<Array<char>>(3, 3);
	if (mat == NULL)
	{
		test_UserInterface::log(false, "mat is NULL!!! Test end.");
		return ++errors;
	}
	const char * a[] = { "aa", "bb", "cc", "dd", "ee", "ff", "gg", "hh", "ii" };
	test_UserInterface::log(true, "Экземпляр матрицы создан.");
	int i = 0;
	for (size_t r = 0; r < (*mat).getRows(); r++)
		for (size_t c = 0; c < (*mat).getCols(); c++)
		{
			(*mat)(r, c) = Array<char>::CreateCopyArray(a[i], sizeof(a[i]));
			strstr((char *)(*mat)(r, c), a[i++]);
		}

	SortMatrix::Sort_by_z8_4(mat);

	i = 0;
	for (size_t r = 0; r < (*mat).getRows(); r++)
		for (size_t c = 0; c < (*mat).getCols(); c++)
		{
			if (r != 0)
				if (strcmp((*mat)(r, c), a[i]) != 0)
				{
					test_UserInterface::log(false, "Отклонение адресации в сортировке. i = ", i);
					errors++;
				}
				else test_UserInterface::log(true, "Элемент, который не должен был измениться, не изменился. i = ", i);
			i++;
		}
	for (size_t c = 0; c < (*mat).getCols() - 1; c++)
	{
		if ((strcmp((*mat)(0, c), (*mat)(0, c + 1)) <= 0) == false) // Если не отсортировано
		{
			test_UserInterface::log(false, "К сожалению, матрица не отсортирована. c = ", c);
			errors++;
		}
		else test_UserInterface::log(true, "Элементы отсортированы. c = ", c);
	}
	delete mat;
	test_UserInterface::log(true, "Тестирование сортировки завершено.");
	return errors;
}

template <typename T>
void z8_4::program::GetStarterSizeMatrix(Matrix<T> * in)
{
	*in = Matrix<T>(
		UserInterface::GetUnsignedInt("Введите количество строк в матрице: ", 1, ~0u),
		UserInterface::GetUnsignedInt("Введите количество стобцов в матрице: ", 1, ~0u)
		);
}

void z8_4::program::GetStarterMatrix(Matrix<int> & in)
{
	char buffer[1024];
	GetStarterSizeMatrix(&in);
	for(size_t i = 0; i < in.getRows(); i++)
		for (size_t j = 0; j < in.getCols(); j++)
		{
#ifndef _MSC_VER
			sprintf(buffer, "Введите целое число для [%lu строки, %lu столбца]", (unsigned long)i, (unsigned long)j);
#else			
			sprintf_s(buffer, sizeof(buffer), "Введите целое число для [%lu строки, %lu столбца]", (unsigned long)i, (unsigned long)j);
#endif
			in(i, j) = UserInterface::GetInt(buffer);
		}
}

void z8_4::program::GetStarterMatrix(Matrix<Array<char>> & in)
{
	char bufferToPrint[128];
	char toSave[1024 * 16];
	GetStarterSizeMatrix(&in);
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

