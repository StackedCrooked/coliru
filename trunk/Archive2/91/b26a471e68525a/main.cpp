#include <iostream>

template<typename Func>
auto call_with_4(Func func) { func(4); }

int main()
{
    auto f = [](int i) { std::cout << "I got a " << i << '\n'; };
    call_with_4(f);
}