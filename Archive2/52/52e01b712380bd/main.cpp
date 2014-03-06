
#include <iostream>

void foo() try { int x; } catch (int) { std::cout<<"Durr."; }

int main() {
    foo();
}