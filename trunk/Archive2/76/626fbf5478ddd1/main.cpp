#include <iostream>
#include <cmath>

double treble(double);

int main()
{
    using namespace std;
    cout << "Enter a number:" << endl;

    double numways;
    cin >> numways;

    numways = treble(numways);

    cout << "Your number trebled is: " << numways << endl;

    return 0;
}

double treble(double n)
{
    using namespace std;
    return n * 3;
}