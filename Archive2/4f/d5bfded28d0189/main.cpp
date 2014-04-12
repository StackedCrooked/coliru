#include <utility>

struct X{
    int f(){ return 0; }
    auto g() -> decltype((this->*(&X::f))()) { return f(); }
};

auto h(X & x) -> decltype((std::declval<X>().*(&X::f))()) { return x.f(); }

int main()
{
    X x;
    return x.g ();
}