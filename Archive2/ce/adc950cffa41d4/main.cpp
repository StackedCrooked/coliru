#include <iostream>

using namespace std;

int main()
{
    int test[5];
    int aux = 0;
    for (int i=0; i<5; i++)
    {
        cout << "ingresa el numero en posicion " << i << endl; //Fill with the number in each position
        cin >> aux;
        test[i] = aux;
    }
    cout << "Valores del array: " <<endl;  // Array values
    for (int i=0; i<5; i++)
    {
        cout << test[i] << endl;
    }
    return 0;
}