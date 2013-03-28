#include <iostream>
#include <string>
#include <vector>

namespace my {
    struct bit_bucket {
        template <typename... T>
        bit_bucket(T&&...) {}
    };
}

#define MY_EXPAND_SIDE_EFFECTS(X) ::my::bit_bucket{ ((X), void(), 0)... }

template <typename T>
void print(T const& t) {
    std::cout << t << '\n';
}

template <typename... T>
void f(T&&... t) {
    MY_EXPAND_SIDE_EFFECTS(print(t));
}

int main()
{
    f(0, 1, 2, 3, 4);
}
