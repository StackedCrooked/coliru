#include <iostream>


namespace a { struct item{}; }

template<typename T>
void func(T t) { do_func(t); }

template void func(a::item);

int main()
{
    func(a::item {});
}

namespace a { void do_func(item) { std::cout << "a::func\n"; } }