#include <iostream>

struct S
{
    int i[];
};

int main() {
    std::cout << sizeof(S) << std::endl;
    
    const int n = 10;
    S* s = new S[n];
    for( int i=0; i<n; ++i )
        std::cout << &s[i] << std::endl;
}