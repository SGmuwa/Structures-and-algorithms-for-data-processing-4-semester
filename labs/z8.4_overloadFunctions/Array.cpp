#include "Array.h"

template<typename T>
z8_4::Array<T>::Array()
{
	data = nullptr;
	length = 0u;
	isCopy = false;
}

template<typename T>
z8_4::Array<T>::Array(T * Data, size_t length, bool needFree)
{
	data = Data;
	Array<T>::length = length;
	isCopy = needFree;
}

template<typename T>
z8_4::Array<T>::~Array()
{
	if (isCopy) delete[] data; 
}


template<typename T>
z8_4::Array<T> z8_4::Array<T>::CreateCopyArray(const T * Data, size_t Length)
{
	T * a = new T[Length];
	memcpy(a, Data, Length * sizeof(T));
	return z8_4::Array<T>::Array<T>(a, Length, true);
}

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

template<typename T>
z8_4::Array<T>::operator T*()
{
	return data;
}