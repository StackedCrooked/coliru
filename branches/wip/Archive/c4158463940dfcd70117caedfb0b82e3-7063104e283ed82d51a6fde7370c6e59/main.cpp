#include <iostream>
using namespace std;

void foo() {
    int x = 5;
    {
        x = 4;
    }
    cout << x << endl;
}

void bar() {
    int x = 5;
    [=] //that's your lambda, implicit by default
    {
        x = 4;
    }();
    cout << x << endl;
}

int main() {
    foo();
    bar();
}