#include <vector>
#include <string>

using namespace std;

class z8_4_test
{
public:
	void z8_4_test_sort_Start()
	{
		z8_4_Matrix<int> a = new z8_4_Matrix<int>(2, 2);
		sort(a.GetData(), MatrixAscending, (size_t)(a.sizeX*a.sizeY));
	}
private:
	bool MatrixAscending(int left, int right)
	{
		return left < right;
	}
	bool MatrixDescending(int left, int right)
	{
		return left > right;
	}
	bool MatrixAscending(vector<char> left, vector<char> right)
	{
		return strcmp(left.data(), left.data()) > 0;
	}
	bool MatrixDescending(vector<char> left, vector<char> right)
	{
		return -strcmp(left.data(), left.data()) > 0;
	}
};