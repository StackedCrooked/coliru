#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
    char decimal[] = {"1.65"};
	double L = atof(decimal);
	cout << atof(decimal) << " " << L << endl;
	return 0;
}