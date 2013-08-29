#include <iostream>
template <unsigned int depth>
int not_quite_recursive(int input) {
    return not_quite_recursive<depth-1>(input) + 
           not_quite_recursive<depth-1>(input);
}
template <>
int not_quite_recursive<0>(int input)
{ return input; }

int main() 
{ std::cout << not_quite_recursive<100>(2); }