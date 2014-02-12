#include <string>
#include <vector>
#include <iostream>


int main()
{
    int pocetSloupcu = 10;
	int pocetRadku = 10;
    char znakPozadi = '-';
    std::vector<std::string> matice;
    matice = std::vector<std::string>(pocetRadku, std::string(pocetSloupcu, znakPozadi));

	matice[5][5] = ' ';

	for (auto& radek : matice)
	{
		std::cout << radek << std::endl;
	}
	return 0;
}