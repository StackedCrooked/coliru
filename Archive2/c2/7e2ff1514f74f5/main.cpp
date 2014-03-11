#include <iostream>

int main() {
    auto append = [](auto &&cnt, auto &&me, 
                     auto &&a, auto &&p1, auto &&...p) -> decltype(auto) 
    { 
        if( not (sizeof...(p) > cnt))
            return a;
        return me(++cnt, me, a << p1, p..., 0);
    };
    append(0, append, std::cout, 1, 2, 3, 4);
}