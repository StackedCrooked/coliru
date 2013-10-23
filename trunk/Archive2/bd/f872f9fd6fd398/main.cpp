#include <iostream>
using namespace std;

int main() {
    int min, hrs, minRem ;

    cout << "Enter hours: "; cin >> hrs;
    cout << "Enter minutes: "; cin >> minRem;

    min = (hrs*60)+minRem;

    cout << hrs << " Hours and " << minRem <<" minutes becomes " << min <<" minuntes" ;

    return 0;
}