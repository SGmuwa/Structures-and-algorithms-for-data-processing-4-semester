#include "purchase.h"
#include "UserInterface.h"

int main(int argc, char * argv[])
{
	FILE * fpIN = UserInterface_OpenFile("file input: ", "rb");
#ifndef _MSC_VER
	FILE * fpOUTtext = fopen("output.txt", "wb");
	FILE * fpOUTbin = fopen("output.bin", "wb");
#else
	FILE * fpOUTtext = NULL;
	FILE * fpOUTbin = NULL;
	fopen_s(&fpOUTtext, "output.txt", "wb");
	fopen_s(&fpOUTbin, "output.bin", "wb");
#endif
	if(fpOUTtext != NULL) fprintf(fpOUTtext, "t");
	else printf("error to work with output.txt\n");
	if(fpOUTbin != NULL) fprintf(fpOUTbin, "b");
	else printf("error to work with output.bin\n");
	char type = '\0';
	fread(&type, sizeof(type), 1, fpIN);
	struct purchase_Array arr;
	switch (type)
	{
	case 't':
		arr = Purchase_Array_fParseln(fpIN);
		break;
	case 'b':
	{
		arr = Purchase_Array_fread(fpIN);
		break;
	}
	default:
		UserInterface_Pause("error: type is not know.");
		return -1;
	}
	
	Purchase_Array_fPrintln(stdout, arr);
	if (fpOUTtext != NULL)
	{
		if(Purchase_Array_fPrintln(fpOUTtext, arr) != arr.length)
			printf("error to save output.txt");
		fclose(fpOUTtext);
	}
	else printf("error of write to output.txt\n");
	if (fpOUTbin != NULL)
	{
		if (Purchase_Array_fwrite(fpOUTbin, arr) != arr.length)
			printf("error to save output.bin");
		fclose(fpOUTbin);
	}
	else printf("error of write to output.bin\n");
	Purchase_Array_quickSort(arr);
	Purchase_Array_fPrintln(stdout, arr);
	unsigned long key = UserInterface_GetUnsignedLongInt("key = ");
	struct purchase * find = Purchase_Array_bynarySearch(arr, key);
	if (find != NULL)
	{
		printf("Index of element: %lu\n", (unsigned long)(find - arr.data));
		Purchase_Println(*find);
	}
	else
		printf("element not found.\n");
	UserInterface_Pause(NULL);
	return 0;
}


