#include <iostream>

int main()
{
    auto ac = alignof('c');    // the alignment of a char

	auto ai = alignof(1);      // the alignment of an int

	auto ad = alignof(2.0);    // the alignment of a double

	int a[20];

	auto aa = alignof(a);      // the alignment of an int
    
    std::cout << ac << " " << ai << " " << ad << " " << aa << "\n";
}