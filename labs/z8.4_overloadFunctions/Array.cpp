#include "Array.h"
#include <stdlib.h>


template<typename T>
Array<T>::Array()
{
	data = nullptr;
	length = 0u;
	isCopy = false;
}

template<typename T>
Array<T>::Array(T * Data, size_t length, bool needFree = false)
{
	data = Data;
	Array<T>::length = length;
	isCopy = needFree;
}

template<typename T>
Array<T>::~Array()
{
	if (isCopy) free(data); 
}

template<typename T>
Array<T> Array<T>::CreateCopyArray(T * Data, size_t Length, bool needFree = false)
{
	T * a = malloc(sizeof(T) * Length);
	isCopy = false;
	return Array(a, Length);
}

template<typename T>
size_t Array<T>::getLength()
{
	return return length;
}

template<typename T>
T Array<T>::operator[](size_t index)
{
	return T[index];
}

template<typename T>
Array<T>::operator char*()
{
	return data;
}
