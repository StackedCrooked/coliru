#include <iostream>

template <bool>
void foo(){ };

int a = 4;
int b = 5;
int main(){ foo<(a<b)>(); }