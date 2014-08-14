#include <iostream>

struct bar{};
struct Foo
{
    Foo(int i, bar) { std::cout << "Foo() " << i << '\n'; }
};

#include <vector>
#include <algorithm>
#include <iterator>
 
int main()
{
    std::vector<Foo> vec;
    unsigned count = 10;
    vec.reserve(count);
    
    unsigned index = 0;
    std::generate_n(std::back_inserter(vec), count, [&]{ return Foo(index++, bar{}); });
}
