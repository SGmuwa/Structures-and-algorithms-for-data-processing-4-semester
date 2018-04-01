
class z8_4_sort
{
public:
	template<typename Element>
	void Sort(Element * Array, bool IsNeedSwitch(Element, Element), size_t CountElements)
	{
		Element * old = Array;
		for (size_t x = 0; x < CountElements; x++)
		{
			for (size_t y = x + 1; y < CountElements; y++)
			{
				if (IsNeedSwitch(Array[x], Array[y])) Switch(Array + x, Array + y);
			}
		}
	}
private:
	template<typename T>
	void Switch(T & a, T & b)
	{
		a = a + b;
		b = a - b;
		a = a - b;
	}
};