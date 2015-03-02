#include <iostream>

template<typename Func>
auto call_with_4(Func func) { func(4); }

void g(int i)
{
    std::cout << "I also got a " << i << '\n';
}

int main()
{
    auto f = [](int i) { std::cout << "I got a " << i << '\n'; };
    call_with_4(f);
    call_with_4(g);
}