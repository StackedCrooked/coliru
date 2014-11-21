#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    vector<vector<int>> table =
	{
		{ 1, 1, 2 },
		{ 1, 1, 5 },
		{ 1, 4, 2 },
		{ 5, 5, 4 }
	};

	vector<pair<int, pair<int, int>>> table2;
	table2.reserve(table.size()*table[0].size());
	for (int r = 0; r < table.size(); r++)
	{
		for (int c = 0; c < table[r].size(); c++)
		{
			table2.push_back(make_pair(table[r][c], make_pair(r, c)));
		}
	}
	sort(table2.begin(), table2.end());

	for (auto i : table2)
		cout << "Value : "<<i.first << "  Mahal :" << i.second.first << " " << i.second.second<<'\n';


}