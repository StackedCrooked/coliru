#include <iostream>

struct item{};

template<typename T>
void func(T t) { do_func(t); }

int main()
{
    func(item{}); // ok
    //func(int{});  // error (adl doesn't work with builtin types)
}

void do_func(item) { std::cout << "do_func(item)\n"; }
void do_func(int) { std::cout << "do_func(int)\n"; }