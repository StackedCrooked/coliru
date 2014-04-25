#include <iostream>

template<int... I>
int f(char) {
    return sizeof...(I);
}

using fptr = int(*)(char);

int main() {
    fptr test = f<1,2,3,4,5>;
    std::cout << test('a');
}