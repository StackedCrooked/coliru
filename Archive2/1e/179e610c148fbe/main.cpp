#include <vector>
#include <iostream>
#include <iterator>
#include <functional>
#include <algorithm>
#include <boost/iterator/indirect_iterator.hpp>

struct foo 
{
    foo(int i) : i(i) {}
    int i;
};

int main()
{
    std::vector<foo*> fooptrs { new foo(1), new foo(10), new foo(100), new foo(1000) };
    std::vector<foo> foos;
    
    std::copy(boost::make_indirect_iterator(fooptrs.begin()),
              boost::make_indirect_iterator(fooptrs.end()),
              std::back_inserter(foos));
    for(auto const& f : foos) {
        std::cout << f.i << ' ';
    }
    std::cout << std::endl;
}
