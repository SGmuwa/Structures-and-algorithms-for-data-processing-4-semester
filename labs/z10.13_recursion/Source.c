#include "UserInterface.h"
#include <stdlib.h>

// ѕоиск максимального значени¤ массива из n целых чисел. ¬озвращает указатель на самый большой
int * p_findMaxIndexInArray(const int * array, size_t length, int * maxIndex)
{
	if (length == 0) return maxIndex;
	maxIndex = *array > *maxIndex ? array : maxIndex;
	return p_findMaxIndexInArray(array + 1, length - 1, maxIndex);
}

// ѕоиск максимального значени¤ массива из n целых чисел. ¬озвращает указатель на самый большой.
int * findMaxIndexInArray(const int * array, size_t length)
{
	if (array == NULL || length == 0) return NULL;
	return p_findMaxIndexInArray(array + 1, length - 1, array);
}

void getInformation(int * array, size_t length)
{
	while (--length != -1)
	{
		printf("array[%3u] = ", (unsigned int)length);
		array[length] = UserInterface_fGetInt(NULL, stdin, NULL);
	}
}

void printArray(const int * array, size_t length)
{
	while (--length != -1) {
		printf("[%3u]%11d\t", (unsigned)length, array[length]);
	}
	printf("\n");
}

int main(int argc, char * argv[])
{
	size_t length = UserInterface_GetUnsignedIntLimit("Length: ", 1, 100);
	int * array = (int *) malloc(length * sizeof(int));
	if (array == NULL) return -1;
	getInformation(array, length);
	printf("____________\n");
	printArray(array, length);
	int * MaxIndex = findMaxIndexInArray(array, length);
	printf("maxValue: [%3d]%11d\n", MaxIndex - array, *MaxIndex);
	free(array);
	UserInterface_Pause("Press any key...");
}