#include <iostream>
#include <iterator>

using namespace std;

enum consts
{
    Sx = 10,
	Sy = 5,
};

class range
{
public:
	range(int min, int max) : min_(min), max_(max)
	{}

	class iterator
	{
	public:
		iterator(int pos) : pos_(pos)
		{}

		bool operator != (const iterator & it)
		{
			return pos_ != it.pos_;
		}

		iterator & operator ++ ()
		{
			++pos_;
			return *this;
		}

		iterator operator ++ (int)
		{
			return{ pos_++ };
		}

		int operator *()
		{
			return pos_;
		}

		int pos_;
	};

	iterator begin()
	{
		return{ min_ };
	}

	iterator end()
	{
		return{ max_ };
	}

	int min_, max_;
};

template<typename Type, int N>
inline void display(Type(&x)[N])
{
	for (auto value : x)
	{
		cout << value << ", ";
	}
}

template<typename Type, int N, int K>
void displayMatrix(Type(&x)[N][K])
{
	for (auto &row : x)
	{
		display(row);
		cout << endl;
	}
}

template<typename Type, int N, int K>
void copy(Type(&dst)[N][K], const Type(&src)[N][K])
{
	for (int x : range(0, N))
	{
		for (int y : range(0, K))
		{
			dst[x][y] = src[x][y];
		}
	}
}

template<typename Type, int N, int K, typename CoreType>
void transform(Type(&mat)[N][K], CoreType core)
{
	for (int x : range(0, N))
	{
		for (int y : range(0, K))
		{
			mat[x][y] = core(x, y);
		}
	}
}

template<typename Type, int N, int K>
void derivative_x(Type(&mat)[N][K])
{
	auto Core = [mat](int pos_x, int pos_y)
	{
		if (pos_x + 1 >= N)
			return 0;
		return mat[pos_x + 1][pos_y] - mat[pos_x][pos_y];
	};
	transform(mat, Core);
}

template<typename Type, int N, int K>
void derivative_y(Type(&mat)[N][K])
{
	auto Core = [mat](int pos_x, int pos_y)
	{
		if (pos_y + 1 >= K)
			return 0;
		return mat[pos_x][pos_y + 1] - mat[pos_x][pos_y];
	};
	transform(mat, Core);
}

int main()
{
	int x1[Sx] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	double x2[Sx] = { 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9 };

	int M[Sx][Sy] = {
		{ 4, 2, 1, 2, 4 },
		{ 2, 1, 0, 1, 2 },
		{ 1, 0, 0, 0, 1 },
		{ 2, 1, 0, 1, 2 },
		{ 4, 2, 1, 2, 4 },
		{ 4, 2, 1, 2, 4 },
		{ 2, 1, 0, 1, 2 },
		{ 1, 0, 0, 0, 1 },
		{ 2, 1, 0, 1, 2 },
		{ 4, 2, 1, 2, 4 },
	};
	int M2[Sx][Sy];
	copy(M2, M);

	cout << "Rezultat1:\n";
	display(x1);
	cout << endl;
	cout << "Rezultat2:\n";
	display(x2);
	cout << endl;
	cout << "Rezultat3:\n";
	displayMatrix(M);
	cout << endl;

	derivative_x(M);
	cout << "Rezultat4:\n";
	displayMatrix(M);
	cout << endl;

	derivative_y(M2);
	cout << "Rezultat5:\n";
	displayMatrix(M2);
	cout << endl;

	cout << "Range: ";
	for (auto i : range(0, 10))
	{
		cout << i << ", ";
	}
	cout << endl;
	
	return 0;
}

