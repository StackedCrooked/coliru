#include <iostream>

    template<int I> struct identity {
        static const int value = I;
    };
    
    template<int A, int B> struct sum {
        static const int value = identity<A>::value + identity<B>::value;
    };

    auto main(int argc, char* argv[]) -> int {
        std::cout << sum<1, 3>::value;
        return 42;
    }