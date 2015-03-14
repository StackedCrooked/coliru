#include <iostream>
using namespace std;

int main()
{
    int n;
    n=0;
    
    cout << "inserisci valore di n" << endl;
    cin >>n;
    if (n>10) {
        cout<<"il valore di n è maggiore di 10";
    }
    else {
        cout<<"il valore di n è minore di 10";
    }
   system("PAUSE");
   return 0;
}