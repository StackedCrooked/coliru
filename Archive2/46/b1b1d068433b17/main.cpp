#include <iostream>
using namespace std;

int main() {
    char poBuffChar[100];
    // p1 == poBuffChar + 10
    void* p1 = (void *)&poBuffChar[10];
    // p2 == poBuffChar + 1000
    void* p2 = (void*)(&poBuffChar)[10];
    // so the difference is 990
    cout << p1 << ' ' << p2 << ' ' << ((char*)p2 - (char*)p1) << endl;
}