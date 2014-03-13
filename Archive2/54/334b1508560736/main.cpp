#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;


int main()
{
    srand (time(NULL)); // semilla
	int begin = -2, end = 4; // principio y fin del rango
	int n = 0;
	cout << "¿Cuantos numeros quieres generar? ";
	cin >> n;

	for (int i=0; i<n; i++)
	{
		double y = (rand() % (end-begin)) + begin + 1; // número aleatorio entre begin y end. Sumo 1 para que el rango sea [-2, 4] y no [-2,4)
		double p = exp (-pow(y-1, 2.0));

		cout << y << "\t"<< p << endl;
	}
	return 0;
}
