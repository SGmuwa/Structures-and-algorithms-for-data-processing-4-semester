#pragma once

#ifndef _INC_ARRAY_
#define _INC_ARRAY_

namespace z8_4
{
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
		Array(T * Data, size_t length, bool needFree);
		~Array();

		// Копирование данных из оперативной памяти в новое место.
		// const T * Data: Передайте указатель, в котором хранятся данные.
		// size_t Length: количество элементов.
		// Возвращает: новый массив.
		static Array<T> CreateCopyArray(const T * Data, size_t Length);



		// Возвращает количество элементов в массиве.
		size_t getLength();

		T operator[](size_t index);

		operator T*();

	private:
		size_t length;
		T * data;
		bool isCopy; //Установите true, если при вызове деконструктора требуется вызвать освобождение free данных. Иначе установите false. По-умолчанию: false.
	};

}

#endif