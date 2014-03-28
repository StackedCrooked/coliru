#include <iostream>

template<int I>
struct blah {
    blah() {
        std::cerr << "blah " << I << std::endl;
    }
};

thread_local static blah<0> BLAH0;
static blah<1> BLAH1;
thread_local static int i = 42;

int main() {
    std::cerr << "main " << i <<  std::endl;
}