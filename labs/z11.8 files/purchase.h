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


	// Считывает текст в формате "purchase: {%lu, %f, %llu}" и помещает содержимое в output.
	// const char * text: Текст, откуда надо производить чтение.
	// struct purchase * ouput: Указатель на место, куда надо выводить результат.
	// Возвращает: True, если чтение было произведено верно. Иначе - False.
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

	// Считывает текст в формате "purchase: {%lu, %f, %llu}" и помещает содержимое в output.
	// FILE * fpIN: Файл, откуда надо производить чтение.
	// struct purchase * ouput: Указатель на место, куда надо выводить результат.
	// Возвращает: True, если чтение было произведено верно. Иначе - False.
	int Purchase_fParseln(FILE * fpIN, struct purchase * output)
	{
		if (output == NULL || fpIN == NULL) return 0;
		return 3 == 
#ifdef _MSC_VER
			fscanf_s
#else
			fscanf
#endif
			(fpIN, "purchase: {%lu, %f, %llu}", &output->CheckNumber, &output->TotalSum, &output->DateTime);
	}

	// Прочитать из файла массив чеков.
	// FILE * input: файл, откуда надо прочитать массив чеков.
	// Возвращает: массив чеков который был прочитан из файла.
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

	// Печатает текст в формате "purchase: {%lu, %f, %llu}" и помещает содержимое в output.
	// FILE * fpOUT: Текст, откуда надо производить чтение.
	// struct purchase * ouput: Указатель на место, куда надо выводить результат.
	// Возвращает: True, если чтение было произведено верно. Иначе - False.
	int Purchase_fPrintln(FILE * fpOUT, struct purchase input)
	{
		if (fpOUT == NULL || ferror(fpOUT) != 0) return 0;
		return 3 == fprintf(fpOUT, "purchase: {%lu, %f, %llu}\n", input.CheckNumber, input.TotalSum, input.DateTime);
	}

	// Печатает текст в формате "purchase: {%lu, %f, %llu}" и помещает содержимое в output.
	// struct purchase * ouput: Указатель на место, куда надо выводить результат.
	// Возвращает: True, если чтение было произведено верно. Иначе - False.
	int Purchase_Println(struct purchase input)
	{
		return Purchase_fPrintln(stdout, input);
	}

	// Прочитать из файла массив чеков.
	// FILE * output: файл, откуда надо прочитать массив чеков.
	// Возвращает: массив чеков который был прочитан из файла.
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

	// Ищет среди массива данных чек с номером key.
	// const struct purchase_Array input: Входной массив данных, где производится поиск. Массив должен быть отсортирован.
	// unsigned long key: ключ-образец.
	// Возвращает: указатель в участке памяти на подходящий элемент.
	struct purchase * Purchase_Array_bynarySearch(const struct purchase_Array input, unsigned long key)
	{
		/* Номер первого элемента в массиве */
		size_t first = 0;
		/* Номер элемента в массиве, СЛЕДУЮЩЕГО ЗА последним */
		size_t last = input.length;

		/* Начальная проверка, которую, в принципе, можно опустить — но тогда см. ниже! */
		if (last == 0) {
			/* массив пуст */
			return NULL;
		}
		else if (input.data[0].CheckNumber > key) {
			/* искомый элемент меньше всех в массиве */
			return NULL;
		}
		else if (input.data[last - 1].CheckNumber < key) {
			/* искомый элемент больше всех в массиве */
			return NULL;
		}

		/* Если просматриваемый участок непустой, first < last */
		while (first < last) {
			size_t mid = first + (last - first) / 2;

			if (key <= input.data[mid].CheckNumber)
				last = mid;
			else
				first = mid + 1;
		}

		/* Если условный оператор if (n == 0) и т.д. в начале опущен -
		* значит, тут раскомментировать!
		*/
		if (/* last < n && */ input.data[last].CheckNumber == key) {
			/* Искомый элемент найден. last - искомый индекс */
			return input.data + last;
		}
		else {
			/* Искомый элемент не найден. Но если вам вдруг надо его
			* вставить со сдвигом, то его место - last.
			*/
			return NULL;
		}
	}


	// Функция, которая ответит, надо ли поменять два элемента, чтобы приблизиться к состоянию "Массив возрастает"
	// cosnt void * min: элемент, который ближе к нулю. Указывает на объект данных struct purchase.
	// const void * max: элемент, который дальше от нуля. Указывает на объект данных struct purchase.
	// Возвращает: True, если элементы следует поменять местами.
	int Purchase_p_isNeedSwap(const void* min, const void* max)
	{
		return ((struct purchase*)min)->CheckNumber >((struct purchase*)max)->CheckNumber;
	}

	// Осуществляет сортировку входного массива
	// struct purchase_Array input: Массив, который требуется в сортировке. 
	void Purchase_Array_quickSort(struct purchase_Array input)
	{
		qsort(input.data, input.length, sizeof(struct purchase), Purchase_p_isNeedSwap);
	}

	// ------------------------------ BINARY FILES --------------------------------------

	struct purchase_Array Purchase_Array_fread(FILE * fpIN)
	{
		struct purchase_Array output;
		unsigned long long buffer;
		fread(&buffer, sizeof(unsigned long long), 1, fpIN);
		output.length = (size_t)buffer;
		output.data = (struct purchase * ) calloc(output.length, sizeof(struct purchase));
		if (output.data == NULL) { output.length = 0; return output; }
		
		/*
		for (int i = 0; i < (int)output.length; i++)
			if (fread(output.data + i, sizeof(struct purchase), 1, fpIN) == 0)
			{
				
				printf("error (%d) to fread i = %d\n", ferror(fpIN), i);
				for (int j = 0; j < sizeof(struct purchase); j++)
				{
					if(fread((char*)(output.data + i) + j, sizeof(char), 1, fpIN) == 0)
						printf("error (%d) to fread byte i = %d j = %d\n", ferror(fpIN), i, j);
				}
			}
			*/
		size_t countAccess = 0;
		if ((countAccess = fread(output.data, sizeof(struct purchase), output.length, fpIN)) != output.length)
		{// Если ошибка
			output.length = countAccess;
		}
		return output;
	}

	size_t Purchase_Array_fwrite(FILE * fpOUT, struct purchase_Array data)
	{
		unsigned long long buffer = data.length;
		fwrite(&buffer, sizeof(buffer), 1, fpOUT);
		return fwrite(data.data, sizeof(struct purchase), data.length, fpOUT);
	}

#ifdef __cplusplus
}
#endif // __cplusplus