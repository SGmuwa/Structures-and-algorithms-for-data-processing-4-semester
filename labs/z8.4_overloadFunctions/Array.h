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
		Array()
		{
			data = nullptr;
			length = 0u;
			isNeedFree = false;
		}
		// Инцилизация массива
		// T * Data: Передайте указатель, в котором хранятся данные.
		// size_t length: количество элементов.
		// bool needFree = false: Установите true, если при вызове деконструктора требуется вызвать освобождение free данных. Иначе установите false. По-умолчанию: false.
		Array(T * Data, size_t length, bool needFree = false)
		{
			data = Data;
			Array<T>::length = length;
			isNeedFree = needFree;
		}
		Array(const Array<T> & input)
		{
			data = input.data;
			this->length = input.length;
			isNeedFree = false;
		}
		~Array()
		{
			if (isNeedFree) delete[] data;
		}

		// Копирование данных из оперативной памяти в новое место. Создаётся экземпляр new!
		// const T * Data: Передайте указатель, в котором хранятся данные.
		// size_t Length: количество элементов.
		// Возвращает: новый массив.
		static Array<T> * CreateCopyArray(const T * Data, size_t Length)
		{
			T * a = new T[Length];
			memcpy(a, Data, Length * sizeof(T));
			//Array<T> * buffer = ;
			return new Array(a, Length, true);
		}



		// Возвращает количество элементов в массиве.
		size_t getLength() const;

		inline T operator[](size_t index);

		template<typename T>
		inline operator T*() const
		{
			return data;
		}

		inline const T * GetConstData() const
		{
			return const data;
		}

	private:
		T * data;
		size_t length;
		bool isNeedFree; //Установите true, если при вызове деконструктора требуется вызвать освобождение free данных. Иначе установите false. По-умолчанию: false.
	};

}

#endif