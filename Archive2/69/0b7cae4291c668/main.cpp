#include <iostream>
#include <string>
using namespace std;

int main()
    {
    string name;
    int pontos;
    pontos = 10;

    cout << pontos +2 << endl;

    double a;
    double b;
    double c;
    a = 1000;
    b = 2000;
    c = 3000;
    cout.precision(10);
    cout << a*b*c << endl;

    float x;
    float y;
    x = 2.2;
    y = 3.3;

    cout.precision(4);
    cout << x/y;


    return 0;
    }
