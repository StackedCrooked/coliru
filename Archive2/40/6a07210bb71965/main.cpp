#include<iostream>
#include<array>
#include<vector>
#include <map>
int NullsIn(int r)
{
    int ret = 0;
	for (int j = 10; j <= r; j *= 10)
	{
		if ((r / j) * j == r)
			++ret;
	}
	return ret;
}

int NullsDifference(int r, int m)
{
	return NullsIn(r*m) - NullsIn(r);
}
int backwardIteration(std::array<int, 3> state, std::vector<std::vector<int> > const& m)
{
	std::cout << state[0] << " " << state[1] << " " << state[2] ;

	static std::map<std::array<int, 3>, int> memoization;
	auto it = memoization.begin();
	while (it != memoization.end()){
		if (it->first.operator[](0) == state[0] && it->first.operator[](1) == state[1])
		{
			std::cout << "   using memo table !\n";
			return it->second;
		}
		++it;
	}

	std::cout << '\n';
	int i = state[0];
	int j = state[1];
	int r = state[2];

	int ret = 0;
	if (i>0 && j>0)
	{
		int inew = i - 1;
		int jnew = j - 1;

		ret = std::min(NullsDifference(r, m[inew][j]) + backwardIteration({ inew, j, r*m[inew][j] }, m),
			NullsDifference(r, m[i][jnew]) + backwardIteration({ i, jnew, r*m[i][jnew] }, m));
	}
	else if (i>0)
	{
		int inew = i - 1;
		ret = NullsDifference(r, m[inew][j]) + backwardIteration({ inew, j, r*m[inew][j] }, m);
	}
	else if (j>0)
	{
		int jnew = j - 1;
		ret = NullsDifference(r, m[i][jnew]) + backwardIteration({ i, jnew, r*m[i][jnew] }, m);
	}

	memoization[state] = ret;
	return ret;
}


int main()
{
	int ncols = 4;
	int nrows = 3;
	std::vector<std::vector<int> > m = { 
		{ 1, 1, 2 }, { 1,1,5 }, { 1, 4, 200 }, {5,5,4}};
	std::array<int, 3> initialState = { ncols - 1, nrows - 1, m[ncols - 1][nrows - 1] };

	for (int i = 0; i < ncols; i++)
		for (int j = 0; j < nrows;j+=2)
			std::cout << "Minimum number of zeros: " << 
			backwardIteration({ i, j, m[i][j] }, m) << "\n" << std::endl;
}
