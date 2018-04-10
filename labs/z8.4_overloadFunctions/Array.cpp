#include "Array.h"



template<typename T>
size_t z8_4::Array<T>::getLength() const
{
	return length;
}

template<typename T>
inline T z8_4::Array<T>::operator[](size_t index)
{
	return data[index];
}

