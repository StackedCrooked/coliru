#include <iostream>
using namespace std;

int division(int a, int b) // Calcule a divisé par b.
{
    return a / b;
}
 
int main()
{
    int a {};
    cout << "Valeur pour a : ";
    cin >> a;
   
    int b;
    cout << "Valeur pour b : ";
    cin >> b;
 
    cout << a << " / " << b << " = " << division(a,b) << endl;
   
    return 0;
}