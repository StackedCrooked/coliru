#include <iostream>


namespace a { struct item{}; }
namespace b { struct item{}; }


template<typename T>
void func(T t) { do_func(t); }


int main()
{    
    func(a::item{});
    func(b::item{});
}


namespace a { void do_func(item) { std::cout << "a::func\n"; } }
namespace b { void do_func(item) { std::cout << "b::func\n"; } }
