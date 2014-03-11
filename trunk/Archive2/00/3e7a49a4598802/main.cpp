#include <memory>
#include <iostream>

struct objs
{
    objs(objs const&) = delete;
    objs& operator=(objs const&) = delete;
    objs& operator=(objs&&) = delete;
    objs(objs&&) = delete;

    std::unique_ptr< int > obj_a;
    
    objs()
        : obj_a(std::unique_ptr< int >( new int(42) ))
        {}
};

int main()
{
    objs o;
    
    auto p = std::move(o.obj_a);
    if(not o.obj_a) std::cout << "Doh!\n";
    std::cout << *p << '\n';
}
