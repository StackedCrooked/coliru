#include <iostream>

template <bool>
void foo(){ };

const int a = 4;
const int b = 5;

int main(){ foo<a<b>(); }