#include <iostream>

int a[] = {1, 2, 4};

int main(){ std::cout << sizeof(a)/sizeof(a[0]) << std::endl; }