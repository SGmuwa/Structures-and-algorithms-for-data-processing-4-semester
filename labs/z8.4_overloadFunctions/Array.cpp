#include "Array.h"










template<typename T>
size_t z8_4::Array<T>::getLength()
{
	return length;
}

template<typename T>
T z8_4::Array<T>::operator[](size_t index)
{
	return data[index];
}

