#include <iostream>
#include <random>
using namespace std;


int main() {
    int n;
	cin >> n;
	double *mas = new double[n];
	for(int i=0; i < n; i++) {
		mas[i] = (double)rand();
		cout << mas[i] << endl;
	}
	return 0;
}