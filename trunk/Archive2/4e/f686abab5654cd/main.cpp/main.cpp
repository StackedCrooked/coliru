#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

void Vypis(const vector<string>& matice)
{
    for (auto prvek : matice)
	{
		cout << prvek << endl;
	}

	cout << endl;
}

int main()
{
	vector<string> matice;
	matice = vector<string>(5, string(5, 'x'));
	matice[1][1] = 'o';
 	
	Vypis(matice);

	// obycejny cyklus for
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			matice[i][j] = '-';
		}
	}

	Vypis(matice);

	// for ranged loop s referenci na radek
	for (auto& radek : matice)
	{
		std::fill(radek.begin(), radek.end(), '+');
	}

	Vypis(matice);

	return 0;
}