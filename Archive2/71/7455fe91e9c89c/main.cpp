#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;
using Table = vector<vector<int>>;

int CountZeros(int number)
{
    if (number < 0)
		return numeric_limits<int>::max();
	int res = 0;
	while (number != 0)
	{
		if (number % 10 == 0)
			res++;
		else break;
		number /= 10;
	}
	return res;
}
const int rows = 2;
const int cols = 3;
Table memo(rows, vector<int>(cols, -1));

int solve(int i, int j, const Table& table)
{
	if (i < 0 || j < 0)return -1;
	if (memo[i][j] != -1)
		return memo[i][j];
	int up = 0, left = 0;
	up = solve(i - 1, j, table)*table[i][j];
	left = solve(i, j - 1, table)*table[i][j];
	
		memo[i][j] = CountZeros(up) < CountZeros(left) ? up : left;

	return memo[i][j];
}
int main()
{
	Table table =
	{
		{ 1, 2, 100 },
		{ 5, 5, 4 }
	};

	memo[0][0] = 1;
	cout << solve(1, 2, table);

}