#include <iostream>

int f(int) { return 5; }
int x = 0;
int main() { for(int y = f(x), y > x; y--) {} std::cout << y; }