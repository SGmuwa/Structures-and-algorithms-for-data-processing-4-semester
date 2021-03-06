﻿#include "program.h"

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
	if(argc > 1) StartTest();
	Matrix<int> * typeINT = nullptr;
	Matrix<const Array<char>*> * typeSTR = nullptr;
	switch (UserInterface::GetChek("С каким типом данных вы будете работать?\n0. Целые числа\n1. Текст", 1))
	{
	case 0:
		MatrixIO::GetStarterMatrix(typeINT, stdin, stdout);
		break;
	default:
		MatrixIO::GetStarterMatrix(typeSTR, stdin, stdout);
		UserInterface::pause("Введите любой символ для продолжения...");
		break;
	}

	SortMatrix::Sort_by_z8_4(typeINT);
	SortMatrix::Sort_by_z8_4(typeSTR);

	MatrixIO::print(typeINT, stdout);
	MatrixIO::print(typeSTR, stdout);

	delete typeINT;
	delete typeSTR;

	UserInterface::pause("Введите любой символ для выхода...");

	return 0;
}

unsigned z8_4::program::StartTest()
{
	unsigned errors = 0;
	test_UserInterface::log(true, "\nТестирование началось.\n");

	for (size_t i = 10; i != 0; i--) // Тестирование утечки памяти.
		Test_ParseToStringInt();
	for (size_t i = 10; i != 0; i--) // Тестирование утечки памяти.
		Test_SortMatrixInt();
	for (size_t i = 10; i != 0; i--) // Тестирование утечки памяти.
		Test_SortMatrixString();

	test_UserInterface::log(true, "\n\n\nИтоговое тестирование:\n", errors);

	errors += Test_ParseToStringInt();
	errors += Test_SortMatrixInt();
	errors += Test_SortMatrixString();

	test_UserInterface::log(errors == 0, "Тестирование окончено. Количество ошибок: ", errors);
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
	z8_4::MatrixIO::toString((const Matrix<int>*)mat, MemoryToString, sizeof(MemoryToString));
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

	MatrixIO::toString((const Matrix<int>*)mat, MemoryToString, sizeof(MemoryToString));
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
	if (mat == NULL)
	{
		test_UserInterface::log(false, "mat is NULL!!! Test end.");
		return ++errors;
	}
	test_UserInterface::log(true, "Экземпляр матрицы создан.");
	int i = 2;
	for (size_t r = 0; r < (*mat).getRows(); r++)
		for (size_t c = 0; c < (*mat).getCols(); c++)
		{
			(*mat)(r, c) = i++;
		}


	/*
	{
	{2, 3, 4}
	{5, 6, 7}
	{8, 9, A}
	}

	*/

	SortMatrix::Sort_by_z8_4(mat);

	/*
	{
	{4, 3, 2}
	{7, 6, 5}
	{A, 9, 8}
	}

	*/

	i = 2;
	for (size_t r = 0, c = 0; i <= 9 - 1 + 2; i++)
	{
		switch (i)
		{ // Способ 1
		case 0x2: r = 0; c = 2; break;
		case 0x3: r = 0; c = 1; break;
		case 0x4: r = 0; c = 0; break;
		case 0x5: r = 1; c = 2; break;
		case 0x6: r = 1; c = 1; break;
		case 0x7: r = 1; c = 0; break;
		case 0x8: r = 2; c = 2; break;
		case 0x9: r = 2; c = 1; break;
		case 0xA: r = 2; c = 0; break;
		default:
			test_UserInterface::log(false, "Ошибка составления тестирования. i = ", i);
			errors++;
			break;
		}
		if ((*mat)(r, c) != i)
		{
			MatrixIO::print(mat, stdout);
			test_UserInterface::log(false, "Ошибка сортировки. i = ", i);
			errors++;
		}
		else test_UserInterface::log(true, "Элемент отсортирован верно. i = ", i);
	}
	if (errors != 0)
		MatrixIO::print(mat, stdout);
	delete mat;
	test_UserInterface::log(true, "Тестирование сортировки завершено.");
	return errors;
}

unsigned z8_4::program::Test_SortMatrixString()
{
	unsigned errors = 0;
	test_UserInterface::log(true, "\nТестирование сортировки (строки).\n");
	Matrix<const Array<char>*> * mat = new Matrix<const Array<char>*>(3, 3);
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
			(*mat)(r, c) = Array<char>::CreateCopyArray(a[i++], 3);
			//strstr((char *)(*mat)(r, c), a[i++]);
		}

	SortMatrix::Sort_by_z8_4(mat);

	i = 0;
	for (size_t r = 0; r < (*mat).getRows(); r++)
		for (size_t c = (*mat).getCols() - 1; c != ~(size_t)0; c--)
			// Способ 2
		{
			if (strcmp((char*)*(*mat)(r, c), a[i]) != 0)
			{
				test_UserInterface::log(false, "Элемент не отсортирован. i = ", i);
				errors++;
			}
			else test_UserInterface::log(true, "Элемент отсортирован. i = ", i);
			i++;
		}
	if(errors != 0)
		MatrixIO::print(mat, stdout);
	MatrixIO::FreeMatrixContent(mat);
	delete mat;
	test_UserInterface::log(true, "Тестирование сортировки завершено.");
	return errors;
}



