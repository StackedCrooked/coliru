#include<iostream>

auto fib = [](auto myself, int x) {
  if(x < 2)
    return 1;
  return myself(x - 1) + myself(x - 2);
};

template<typename F>
struct P {
    F f;
    P(F f): f(f) {};
    template<typename X>
    auto operator()(X x) {
        return f(*this, x);
    }
};

template<typename F>
auto Y(F f) {
    return P<F>{f};
}


int main() {
    for(int i = 0; i < 10; i++) {
        std::cout << i << " -> " << Y(fib)(i) << '\n';
    }
}