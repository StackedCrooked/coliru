#include <iostream>
#include <limits>
using namespace std;

int main(){
    // Określenie znaku:
	cout << "int - typ ze znakiem: " << numeric_limits<int>::is_signed << endl;
	cout << "unsigned long - typ ze znakiem: " << numeric_limits<unsigned long>::is_signed << endl;

	// Określenie ilości cyfr na przechowanie zmiennej o określonej podstawie:
	cout << "\n";
	cout << "bool - ilosc cyfr: " << numeric_limits<bool>::digits << endl;
	cout << "unsigned char - ilosc cyfr: " << numeric_limits<unsigned char>::digits << endl;
	cout << "double - ilosc cyfr: " << numeric_limits<double>::digits << endl;

	// Czy posiada wartość nieskończoną?
	cout << "\n";
	cout << "bool - zdefiniowana nieskonczonosc: " << numeric_limits<bool>::has_infinity << endl;
	cout << "float - zdefiniowana nieskonczonosc: " << numeric_limits<float>::has_infinity << endl;

	if (numeric_limits<float>::has_infinity)
		cout << "Nieskonczonosc w float: " << numeric_limits<float>::infinity() << endl;

	// Wartosc maksymalna (klasa numeric_limits oraz makra z <climits>):
	cout << "\n";
	cout << "char - wartosc max (numeric_limits<bool>::max()): " << (int)numeric_limits<char>::max() << endl;
	cout << "char - wartosc max (CHAR_MAX): " << CHAR_MAX << endl;

	return 0;
}
