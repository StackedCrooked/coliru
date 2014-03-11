#include <iostream>
#include <string>


int main () {

    int i (42);
    [] { std::cout << i; }();

}