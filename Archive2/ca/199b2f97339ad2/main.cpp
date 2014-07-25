#include "stdafx.h"
#include <iostream>
#include <cmath>

using namespace std;

int main(int argc, char* argv[])
{
    int X = 0;

    double a, b, c, xMin, xMax;

    double y = 0;

    cout << "#1(A): ";
    cin >> a;

    cout << "\n#2(B): ";
    cin >> b;

    cout << "\#3(C): ";
    cin >> c;


    cout << "Enter Xmin" << endl;
    cin >> xMin;

    cout << "Enter Xmax" << endl;
    cin >> xMax;


    y = a + b + c + X;

    for (int count = xMin; count <= xMax; count++)
    {
        cout << count << "\t" << y << "\n";
    }

    return 0;
}