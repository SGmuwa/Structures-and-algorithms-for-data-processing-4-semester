// Создать структуру которая хранит: {price, описание}
// Реализовать чтение данных из консоли
// Реализовать запись данных в консоль
// Реализовать запись структуры в бинарный файл
// Реализовать чтение структуры из бинарного файла


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct String {
	char * message;
	size_t len;
};

struct ElmBD {
	unsigned long price;
	struct String * message;
};

struct ElmBD_Array
{
	struct ElmBD * elms;
	size_t length;
};

#define TRUE 1
#define FALSE 0

// Запрашивает целое беззнаковое число у пользователя.
// char * message: сообщение, которое увидит пользователь.
// Возвращает: Целое беззнаковое число, которое передал пользователь или поток.
unsigned UserInterface_GetUnsignedInt(char * message, FILE * fpIN, FILE * fpOUT)
{
	unsigned buffer = 0;
	unsigned char limit = ~0u;
	while (--limit != 0)
	{
#ifdef _MSC_VER // С помощью данной дерективы мы понимаем, какой компилятор.
		fprintf_s(fpOUT, "%s", message); // Для компилятора Visual Studio
#else
		fprintf(fpOUT, "%s", message); // Для других компиляторов. Стандарт ANSI C.
#endif // _MSC_VER
		if ( // Если
#ifdef _MSC_VER // Для компилятора visual studio.
			fscanf_s(fpIN, "%u", &buffer) // Количество прочтённых элементов.
#else // Для компиляторов стандарта ANSI C.
			fscanf(fpIN, "%u", &buffer) // Количество прочтённых элементов.
#endif // _MSC_VER
			>= 1 // Равно или более 1, то
			)
		{
			break; // Закончить алгоритм.
		}
		// Если всё-таки данные введены не верно, то
#ifdef _MSC_VER
		fscanf_s(fpIN, "%*s"); // Пропускаем неподходящие данные.
#else
		fscanf(fpIN, "%*s"); // Пропускаем неподходящие данные.
#endif // _MSC_VER
	}
	// Когда вышли из цикла, то
	if (limit == 0) // Если лимит был превышен.
	{
		// Печатаем ошибку и выходим.
#ifdef _MSC_VER
		fprintf_s(fpIN, "Error to read. Read data is stop!\n");
#else
		fprintf(fpIN, "Error to read. Read data is stop!\n");
#endif // _MSC_VER
	}
#ifdef _MSC_VER
	fscanf_s(fpIN, "%*c"); // Пропускаем разделитель данных (например, пробел или новая строка)
#else
	fscanf(fpIN, "%*c"); // Пропускаем разделитель данных (например, пробел или новая строка)
#endif // _MSC_VER
	return buffer;
}

// Получение строки от пользователя с поддержкой остановки.
// char * message: сообщение, которое увидит пользователь.
// char * To: указатель, который указывает на тот участок памяти, куда нужно записать результат
// size_t countTo: количество доступных байт в To.
// FILE * fpIN: указать поток ввода информации в программу.
// Возвращает: количество прочтённых символов.
size_t UserInterface_GetStr(char * message, char * To, size_t countTo, FILE * fpIN, FILE * fpOUT)
{
	fprintf(fpOUT, "%s Use CTRL + 2 for end.\n", message);
	char * i = To - 1; // Уменьшаем на 1, так как в цикле будет прибавление
	do {
#ifdef _MSC_VER // Для компилятора Visual Studio
		fread_s(++i, i - To + 1, sizeof(char), 1, fpIN); 
#else // Для компиляторов ANSI C.
		fread(++i, sizeof(char), 1, fpIN); // На каждой новой итерации прибавляем i и записываем 1 символ в To.
#endif // _MSC_VER
	} while (*i >= 0x09 && i != To + countTo - 2); // -1 из-за того, что sizeof возвращает количество, а не последний элемент.
												   // -1 из-за того, чтобы не вошёл в цикл и не стал записьвать в 256 элемент.
																																																// неактуально: -1 из-за того, чтобы добавить ещё нулевой символ.
												   // Цикл повторяется, пока пользователь не введёт какой-либо управляющий символ.
												   // https://ru.wikipedia.org/wiki/Управляющие_символы

	*(i) = '\0'; // Добавляем последний символ.
	return i - To + 1; // +1 так как нужно количество элементов, а не расстояние между первым и последним.
}

struct ElmBD * ElmBD_constructMalloc(unsigned long price, struct String * message)
{
	struct ElmBD * output = (struct ElmBD *) malloc(sizeof(struct ElmBD));
	output->price = price;
	output->message = message;
	return output;
}

struct String * String_constructMalloc(char * message, size_t len)
{
	struct String * output = (struct String *) malloc(sizeof(struct String));
	output->message = message;
	output->len = len;
	return output;
}

// Создаёт копию message
struct String * String_constructCopyMalloc(char * message, size_t len)
{
	struct String * output = (struct String *) malloc(sizeof(struct String));
	output->message = (char *)malloc(sizeof(char)*len);
	//strcpy(output->message, message); // Создаёт копию.
	memcpy(output->message, message, len);
	output->len = len;
	return output;
}



// Спрашивает у пользователя 1 строку БД
struct ElmBD ElmBD_getUserDataElmMalloc(FILE * fpIN, FILE * fpOUT)
{
	unsigned price = 0;
	price = UserInterface_GetUnsignedInt("price: ", fpIN, fpOUT);
	char buffer[128*1024] = { 0 };
	struct String * str = String_constructCopyMalloc(buffer, 
		UserInterface_GetStr("Input message.", buffer, sizeof(buffer), fpIN, fpOUT) // Ниже привёл тот же алгоритм с более понятным кодом.
		); // Данный способ позволяет сократить программу на 1 переменную.
	struct ElmBD output = { price, str };
											/*output.price = price;
											output.message = str;*/
	return output;

	/*
	size_t a = UserInterface_GetStr("Input message.", buffer, sizeof(buffer), fpIN, fpOUT)
	struct String * str = String_constructCopyMalloc(buffer, a);
	*/
}

// Функция запрашивает у пользователя все строки базы данных
struct ElmBD_Array ElmBD_getUserDataAllMalloc(FILE * fpIN, FILE * fpOUT)
{
	struct ElmBD_Array output = { 0, 0 };
	// Получаем от пользователя количество строк в базе данных
	output.length = UserInterface_GetUnsignedInt("count in DB: ", fpIN, fpOUT);
	// Выделяем память для всех этих элементов:
	output.elms = (struct ElmBD *) malloc(sizeof(struct ElmBD)*output.length);
	for (unsigned i = 0; i < output.length; i++)
	{
		output.elms[i] = ElmBD_getUserDataElmMalloc(fpIN, fpOUT);
		//fprintf(fpOUT, "%s", output.elms[i].message->message);
	}
	return output;
}

// Печатает в строковой файл
void ElmBD_PrintData(FILE * fp, const struct ElmBD_Array input)
{
	fprintf(fp, "%u\n", input.length);
	for (unsigned i = 0; i < input.length; i++)
	{
		fprintf(fp, "%u\n", input.elms[i].price); // \n является разделителем.
		fprintf(fp, "%s", input.elms[i].message->message);
		fwrite("\0\n", sizeof(char), 1, fp); // // Нужно вводить признак конца текста. В качестве него вводится \0. \n является разделителем.
		// Используется функция fwrite, так как fprintf не поддерживает печать символа '\0'.
	}
}

// Печатает в бинарный файл
void ElmBD_Write_ElmsBD_ToBinary(const struct ElmBD * bd, unsigned count, FILE * fp)
{
	fwrite(&(count), sizeof(unsigned), 1, fp); // Хватило ли места на диске?
	for (unsigned i = 0; i < count; i++)
	{
		fwrite(&(bd[i].price), sizeof(unsigned), 1, fp); // index строки
		fwrite(&(bd[i].message->len), sizeof(unsigned), 1, fp); // количество символов
		fwrite((bd[i].message->message), sizeof(char), bd[i].message->len, fp); // сообщение
	}
}

// Чтените из бинарного файла
struct ElmBD_Array ElmBD_Read_ElmsBD_FromBinaryMalloc(FILE * fp)
{
	struct ElmBD_Array output = { 0, 0 };
	fread(&(output.length), sizeof(unsigned), 1, fp);
	output.elms = (struct ElmBD *) malloc(sizeof(struct ElmBD)*output.length);

	/*elms = (struct ElmBD *) malloc(sizeof(struct ElmBD)*length);
	elms->price;
	elms[0].price == elms->price;
	elms[1].price == (elms + 1)->price;
	elms[i].price == (elms + i)->price;*/


	for (unsigned i = 0; i < output.length; i++)
	{
		fread(&(output.elms[i].price), sizeof(unsigned), 1, fp);
		output.elms[i].message = (struct String *) malloc(sizeof(struct String)*1);
		fread(&(output.elms[i].message->len), sizeof(unsigned), 1, fp); // В нашем массиве данных находятся строки. У каждой строки есть адрес. Мы обращаемся по адресу i. У каждой строки есть ИД и СООБЩЕНИЕ. В СООБЩЕНИЕ есть ОПИСАНИЕ и ДЛИННА ОПИСАНИЯ. Читаем из файла длинну описания.
		output.elms[i].message->message = (char *)malloc(sizeof(char) * output.elms[i].message->len);
		fread((output.elms[i].message->message), sizeof(char), output.elms[i].message->len, fp);
	}
	return output;
}

int main(int argc, char * argv[])
{
	char filename[1024] = { 0 };
	UserInterface_GetStr("file: ", filename, sizeof(filename), stdin, stdout);
	FILE * INPUT = fopen(filename, "r");
	if (INPUT == NULL) return;
	struct ElmBD_Array userDATA = ElmBD_getUserDataAllMalloc(INPUT, stdout);
	fclose(INPUT);

	ElmBD_PrintData(stdout, userDATA);
	FILE * fpout_bin = fopen("binary_out.bin", "wb");
	FILE * fpout_txt = fopen("text_out.txt", "w");
	ElmBD_PrintData(fpout_txt, userDATA); // Печать массива данных
	ElmBD_Write_ElmsBD_ToBinary(userDATA.elms, userDATA.length, fpout_bin);
	fclose(fpout_txt);
	fclose(fpout_bin);
	//ElmBD_destroy(userDATA); // деконструктор, очитска памяти.

	struct ElmBD_Array userDATA2;
	FILE * fpin_bin = fopen("binary_out.bin", "rb");
	userDATA2 = ElmBD_Read_ElmsBD_FromBinaryMalloc(fpin_bin);
	fclose(fpin_bin);
	ElmBD_PrintData(stdout, userDATA2); // Печать массива данных

	struct ElmBD_Array userDATA3;
	FILE * fpin_txt = fopen("text_out.txt", "r");
	userDATA2 = ElmBD_getUserDataAllMalloc(fpin_bin, stdout);
	fclose(fpin_txt);
	ElmBD_PrintData(stdout, userDATA2); // Печать массива данных

	getch();
}
