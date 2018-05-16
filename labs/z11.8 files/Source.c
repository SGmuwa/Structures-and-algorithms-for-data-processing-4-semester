#include "purchase.h"
#include "UserInterface.h"

int main(int argc, char * argv[])
{

	struct purchase_Array arr = Purchase_Array_fParseln(stdin);
	Purchase_Array_fPrintln(stdout, arr);
	Purchase_Array_quickSort(arr);
	unsigned long key = UserInterface_GetUnsignedLongInt("key = ");
	struct purchase * find = Purchase_Array_bynarySearch(arr, key);
	printf("Number of element: %lu\n", (unsigned long)(arr.data) - (unsigned long)(find));
	Purchase_Println(*find);
	UserInterface_Pause(NULL);
}


