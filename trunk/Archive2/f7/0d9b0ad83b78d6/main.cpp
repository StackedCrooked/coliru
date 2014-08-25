#include <iostream>
#include <cmath>
using namespace std;

void verificarPalindromo(int x)
{

int arregloDeNumero[6];
int diferencia=0;

for (int i=5;i>=0;i--){

    cout << "the number X is: " << x; 
    cout << " and the difference is: " << diferencia << endl;

    arregloDeNumero[i]= ((x-diferencia)/pow(10,i));

    cout << "array of i= " << i << " is: " << arregloDeNumero[i];
    cout << " and the difference is: " << diferencia << endl;

    diferencia+=(arregloDeNumero[i]*pow(10,i));

    cout << "the new difference is: " << diferencia << endl;

}
}

int main() {
    verificarPalindromo(90009);
}