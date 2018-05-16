#pragma

#include <time.h>
#include <stdio.h>
#include <stdlib.h>


#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

	struct purchase
	{
		unsigned long CheckNumber; // searcher
		float TotalSum;
		time_t DateTime;
	};

	struct purchase_Array
	{
		struct purchase * data;
		size_t length;
	};

	// ------------------------------ PARSE ------------------------------------------------


	// ��������� ����� � ������� "purchase: {%lu, %f, %llu}" � �������� ���������� � output.
	// const char * text: �����, ������ ���� ����������� ������.
	// struct purchase * ouput: ��������� �� �����, ���� ���� �������� ���������.
	// ����������: True, ���� ������ ���� ����������� �����. ����� - False.
	int Purchase_sParse(const char * text, struct purchase * output)
	{
		if (output == NULL || text == NULL) return 0;
		return 3 ==
#ifdef _MSC_VER
			sscanf_s
#else
			sscanf
#endif
			(text, "purchase: {%lu, %f, %llu}", &output->CheckNumber, &output->TotalSum, &output->DateTime);
	}

	// ��������� ����� � ������� "purchase: {%lu, %f, %llu}" � �������� ���������� � output.
	// FILE * fpIN: ����, ������ ���� ����������� ������.
	// struct purchase * ouput: ��������� �� �����, ���� ���� �������� ���������.
	// ����������: True, ���� ������ ���� ����������� �����. ����� - False.
	int Purchase_fParseln(FILE * fpIN, struct purchase * output)
	{
		if (output == NULL || fpIN == NULL) return 0;
		return 3 == 
#ifdef _MSC_VER
			fscanf_s
#else
			fscanf
#endif
			(fpIN, "purchase: {%lu, %f, %llu}\n", &output->CheckNumber, &output->TotalSum, &output->DateTime);
	}

	// ��������� �� ����� ������ �����.
	// FILE * input: ����, ������ ���� ��������� ������ �����.
	// ����������: ������ ����� ������� ��� �������� �� �����.
	struct purchase_Array Purchase_Array_fParseln(FILE * input)
	{
		struct purchase_Array output = { 0, 0 };
		if (input == NULL || ferror(input) != 0) return output;
#ifdef _MSC_VER
		fscanf_s
#else
		fscanf
#endif
		(input, "%lu: ", (unsigned long int *)&output.length);
		output.data = (struct purchase *) malloc(sizeof(struct purchase) * output.length);
		for (size_t i = 0; i < output.length; i++)
		{
			if (ferror(input) != 0)
			{
				output.length = i;
				return output;
			}
			Purchase_fParseln(input, output.data + i);
#ifdef _MSC_VER
			fscanf_s
#else
			fscanf
#endif
			(input, " ");
		}
		return output;
	}

	// ------------------------------ PRINT ------------------------------------------------

	// �������� ����� � ������� "purchase: {%lu, %f, %llu}" � �������� ���������� � output.
	// FILE * fpOUT: �����, ������ ���� ����������� ������.
	// struct purchase * ouput: ��������� �� �����, ���� ���� �������� ���������.
	// ����������: True, ���� ������ ���� ����������� �����. ����� - False.
	int Purchase_fPrintln(FILE * fpOUT, struct purchase input)
	{
		if (fpOUT == NULL || ferror(fpOUT) != 0) return 0;
		return 3 == fprintf(fpOUT, "purchase: {%lu, %f, %llu}\n", input.CheckNumber, input.TotalSum, input.DateTime);
	}

	// �������� ����� � ������� "purchase: {%lu, %f, %llu}" � �������� ���������� � output.
	// struct purchase * ouput: ��������� �� �����, ���� ���� �������� ���������.
	// ����������: True, ���� ������ ���� ����������� �����. ����� - False.
	int Purchase_Println(struct purchase input)
	{
		return Purchase_fPrintln(stdout, input);
	}

	// ��������� �� ����� ������ �����.
	// FILE * output: ����, ������ ���� ��������� ������ �����.
	// ����������: ������ ����� ������� ��� �������� �� �����.
	size_t Purchase_Array_fPrintln(FILE * output, struct purchase_Array input)
	{
		if (input.data == NULL || input.length == 0 || ferror(output) != 0) return 0u;
		fprintf(output, "%lu: ", (unsigned long int)input.length);
		for (size_t i = 0; i < input.length; i++)
		{
			if (ferror(output) != 0)
			{
				return i;
			}
			Purchase_fPrintln(output, input.data[i]);
			fprintf(output, " ");
		}
		fprintf(output, "\n");
		return input.length;
	}


	// --------------------------------- binary search --------------------------------

	// ���� ����� ������� ������ ��� � ������� key.
	// const struct purchase_Array input: ������� ������ ������, ��� ������������ �����. ������ ������ ���� ������������.
	// unsigned long key: ����-�������.
	// ����������: ��������� � ������� ������ �� ���������� �������.
	struct purchase * Purchase_Array_bynarySearch(const struct purchase_Array input, unsigned long key)
	{
		if (input.length == 0 || input.data == NULL) return input.data;
		size_t i = input.length / 2;
		size_t numberOfTry = 0;
		while (numberOfTry < input.length / 2 + 1)
		{
			numberOfTry++;
			if (input.data[i].CheckNumber > key)
				i += i >> numberOfTry;
			else if (input.data[i].CheckNumber < key)
				i -= i >> numberOfTry;
			else return input.data + i;
		}
		return NULL; // ������ �������� �� �������.
	}


	// �������, ������� �������, ���� �� �������� ��� ��������, ����� ������������ � ��������� "������ ����������"
	// cosnt void * min: �������, ������� ����� � ����. ��������� �� ������ ������ struct purchase.
	// const void * max: �������, ������� ������ �� ����. ��������� �� ������ ������ struct purchase.
	// ����������: True, ���� �������� ������� �������� �������.
	int Purchase_p_isNeedSwap(const void* min, const void* max)
	{
		return ((struct purchase*)min)->CheckNumber >((struct purchase*)max)->CheckNumber;
	}

	// ������������ ���������� �������� �������
	// struct purchase_Array input: ������, ������� ��������� � ����������. 
	void Purchase_Array_quickSort(struct purchase_Array input)
	{
		qsort(input.data, input.length, sizeof(struct purchase), Purchase_p_isNeedSwap);
	}


#ifdef __cplusplus
}
#endif // __cplusplus