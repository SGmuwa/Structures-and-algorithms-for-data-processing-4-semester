// Создать структуру которая хранит: {id, описание}
// Реализовать чтение данных из консоли
// Реализовать запись данных в консоль
// Реализовать запись структуры в бинарный файл
// Реализовать чтение структуры из бинарного файла


#include <stdio.h>
#include <string.h>

struct String {
	char * message;
	size_t len;
};

struct ElmBD {
	unsigned long id;
	struct String * message;
};

struct ElmBD_Array
{
	struct ElmBD * elms;
	size_t length;
};

struct ElmBD * ElmBD_constructMalloc(unsigned long id, struct String * message)
{
	struct ElmBD * output = (struct ElmBD *) malloc(sizeof(struct ElmBD));
	output->id = id;
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
	strcpy(output->message, message); // Создаёт копию.
	output->len = len;
	return output;
}

// Спрашивает у пользователя 1 строку БД
struct ElmBD ElmBD_getUserDataElmMalloc(unsigned id, FILE * fpIN, FILE * fpOUT)
{
	char * buffer[256] = { 0 };
	fprintf(fpOUT, "[%lu]message: ", id);
	fgets(buffer, sizeof(buffer), fpIN);
	struct String * str = String_constructCopyMalloc(buffer, strlen(buffer) + 1);
	struct ElmBD output = { id, str };
											/*output.id = id;
											output.message = str;*/
	return output;
}

// Функция запрашивает у пользователя все строки базы данных
struct ElmBD_Array ElmBD_getUserDataAllMalloc(FILE * fpIN, FILE * fpOUT)
{
	struct ElmBD_Array output = { 0, 0 };
	fprintf(fpOUT, "count in DB:");
	fscanf(fpIN, "%u", &(output.length));
	output.elms = (struct ElmBD *) malloc(sizeof(struct ElmBD)*output.length);
	for (unsigned i = 0; i < output.length; i++)
	{
		output.elms[i] = ElmBD_getUserDataElmMalloc(i, fpIN, fpOUT);
	}
	return output;
}

// Печатает в строковой файл
void ElmBD_PrintData(FILE * fp, struct ElmBD * elms, unsigned count)
{
	fprintf(fp, "%u\n", count);
	for(unsigned i = 0; i < count; i++)
		fprintf(fp, "%s\n", elms[i].message->message); 
}

// Печатает в бинарный файл
void ElmBD_Write_ElmsBD_ToBinary(const struct ElmBD * bd, unsigned count, FILE * fp)
{
	fwrite(&(count), sizeof(unsigned), 1, fp); // Хватило ли места на диске?
	for (unsigned i = 0; i < count; i++)
	{
		fwrite(&(bd[i].id), sizeof(unsigned), 1, fp); // index строки
		fwrite(&(bd[i].message->len), sizeof(unsigned), 1, fp); // количество символов
		fwrite(&(bd[i].message->message), sizeof(char), bd[i].message->len, fp); // сообщение
	}
}

// Чтените из бинарного файла
struct ElmBD_Array ElmBD_Read_ElmsBD_FromBinaryMalloc(FILE * fp)
{
	struct ElmBD_Array output = { 0, 0 };
	fread(&(output.length), sizeof(unsigned), 1, fp);
	output.elms = (struct ElmBD *) malloc(sizeof(struct ElmBD)*output.length);

	/*elms = (struct ElmBD *) malloc(sizeof(struct ElmBD)*length);
	elms->id;
	elms[0].id == elms->id;
	elms[1].id == (elms + 1)->id;
	elms[i].id == (elms + i)->id;*/


	for (unsigned i = 0; i < output.length; i++)
	{
		fread(&(output.elms[i].id), sizeof(unsigned), 1, fp);
		output.elms[i].message = (struct String *) malloc(sizeof(struct String)*1);
		fread(&(output.elms[i].message->len), sizeof(unsigned), 1, fp); // В нашем массиве данных находятся строки. У каждой строки есть адрес. Мы обращаемся по адресу i. У каждой строки есть ИД и СООБЩЕНИЕ. В СООБЩЕНИЕ есть ОПИСАНИЕ и ДЛИННА ОПИСАНИЯ. Читаем из файла длинну описания.
		output.elms[i].message->message = (char *)malloc(sizeof(char) * output.elms[i].message->len);
		fread(&(output.elms[i].message->message), sizeof(char), output.elms[i].message->len, fp);
	}
	return output;
}

int main(int argc, char * argv[])
{
	struct ElmBD_Array userDATA = ElmBD_getUserDataAllMalloc(stdin, stdout);
	ElmBD_PrintData(stdout, userDATA.elms, userDATA.length);
	FILE * fpout_bin = fopen("binary_out.bin", "wb");
	FILE * fpout_txt = fopen("text_out.txt", "w");
	ElmBD_PrintData(fpout_txt, userDATA.elms, userDATA.length);
	ElmBD_Write_ElmsBD_ToBinary(userDATA.elms, userDATA.length, fpout_bin);
	fclose(fpout_txt);
	fclose(fpout_bin);
	//ElmBD_destroy(userDATA); // деконструктор, очитска памяти.

	struct ElmBD_Array userDATA2;
	FILE * fpin_bin = fopen("binary_out.bin", "rb");
	userDATA2 = ElmBD_Read_ElmsBD_FromBinaryMalloc(fpin_bin);
	fclose(fpin_bin);
	ElmBD_PrintData(stdout, userDATA2.elms, userDATA2.length);

	struct ElmBD_Array userDATA3;
	FILE * fpin_txt = fopen("text_out.txt", "r");
	userDATA2 = ElmBD_getUserDataAllMalloc(fpin_bin, stdout);
	fclose(fpin_txt);
	ElmBD_PrintData(stdout, userDATA2.elms, userDATA2.length);

	getch();
}