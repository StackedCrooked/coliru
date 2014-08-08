
#include <vector>
#include <iostream>

class A {
    int a = fun() , b;
    static int fun() {return b;}
};

int main () {
    A a;
}