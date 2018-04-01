#pragma once
template <typename T>
class Array
{
public:
	// Инцилизация пустого массива. На практике не применяется.
	Array();
	// Инцилизация массива
	// T * Data: Передайте указатель, в котором хранятся данные.
	// size_t length: количество элементов.
	// bool needFree = false: Установите true, если при вызове деконструктора требуется вызвать освобождение free данных. Иначе установите false. По-умолчанию: false.
	Array(T * Data, size_t length, bool needFree = false);
	~Array();

	// Копирование данных из оперативной памяти в новое место.
	// T * Data: Передайте указатель, в котором хранятся данные.
	// size_t length: количество элементов.
	// bool needFree = false: Установите true, если при вызове деконструктора требуется вызвать освобождение free данных. Иначе установите false. По-умолчанию: false.
	// Возвращает: новый массив.
	static Array<T> CreateCopyArray(T * Data, size_t length, bool needFree = false);

	// Возвращает количество элементов в массиве.
	size_t getLength();
	
	T operator[](size_t index);

	operator char*();
	
private:
	size_t length;
	T * data;
	bool isCopy;
};

