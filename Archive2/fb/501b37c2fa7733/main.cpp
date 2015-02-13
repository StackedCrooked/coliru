
#include <vector>
#include <list>
#include <iostream>

template <class Range, class Func, class Elem=decltype(*std::declval<Range>().begin())> 
void terse_for(Range&& range, Func&& func) 
{   for (auto&& x : range) {func(x);}
} 

int main()
{
    std::vector<bool> container{true, true, false, true};

    std::vector<int> v{1,2,3,4};
    terse_for(container, [](auto&& i){i = false;});
    terse_for(v, [](auto&& i){std::cout << i;});
}