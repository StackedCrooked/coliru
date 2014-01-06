#include <iostream>
#include <exception>

using namespace std;

struct Bar {
    enum { number = 42 };
};

int main()
{
    Bar bar;
    cout << bar.number << endl;
}