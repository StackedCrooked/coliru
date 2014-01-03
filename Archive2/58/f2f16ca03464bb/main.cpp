#include <iostream>
#include <string>
#include <vector>

template<class T>
void print(T parameter) {
    using namespace std;
    cout << parameter << endl;
}
int main()
{
    double a = 1.0;
    print(a);
}
