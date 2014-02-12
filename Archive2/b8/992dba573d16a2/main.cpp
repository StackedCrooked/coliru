#include <string>
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    int pocetSloupcu = 10;
	int pocetRadku = 10;
	vector<string> pole(pocetRadku, string(pocetSloupcu, 'x'));
	pole[5][5] = ' ';

	for (auto& radek : pole)
	{
		cout << radek << endl;
	}
	return 0;
}