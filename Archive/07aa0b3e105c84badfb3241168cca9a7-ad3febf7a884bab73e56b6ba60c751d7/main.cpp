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


namespace a { namespace aa { void do_func(item) { std::cout << "a::func\n"; } } using aa::do_func; }
namespace b { inline namespace { void do_func(item) { std::cout << "b::func\n"; } } }
