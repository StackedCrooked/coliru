#include <functional>
#include <iostream>

void func(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8, int p9, int p10, int p11, int p12, int p13, int p14, int p15, int p16
#ifdef USE_17_PARAMS
    , int p17
#endif
         ) {
    // ...
    std::cout << "Hello, World!" << std::endl;
}

int main() {
    using namespace std::placeholders;
    std::function<void(int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int
#ifdef USE_17_PARAMS
        , int
#endif
    )> f = std::bind(func, _1, _2,  _3,  _4,  _5,  _6,  _7,  _8,  _9,  _10, _11, _12, _13, _14, _15, _16
#ifdef USE_17_PARAMS
        , _17
#endif
    );
        
    f(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
#ifdef USE_17_PARAMS
        , 17
#endif
    );
    return 0;
}