#include <iostream>
#include <tuple>

struct A {
    A(int x, int y) {
        std::cout << x << ' ' << y << std::endl;
    }
};

struct B {
    B(A, float) {
    }
};

template<typename... Args>
struct I {
    std::tuple<Args...> args;
    
    I(Args&&... args) : args{std::forward<Args>(args)...} {
    }
    
    template<typename T>
    operator T() {
        return T(std::get<0>(args), std::get<1>(args));
    }
};

template<typename... Args>
I<Args...> _(Args&&... args) {
    return {std::forward<Args>(args)...};
}

int main()
{
    B{{1, 2}, .1f};
    B b1 = {{2, 3}, .1f};
    (void)b1;
    
    B{_(3, 4), .1f};
    B b2 = _(_(4, 5), .1f);
    (void)b2;
}
