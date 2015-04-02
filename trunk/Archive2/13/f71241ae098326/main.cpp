#include <iterator>

namespace range_access {
    using std::begin;
    using std::end  ;
    
    template <typename T>
    auto begin( T&& t ) -> decltype(begin(t)) {return begin(t);}
    template <typename T>
    auto end( T&& t ) -> decltype(end(t)) {return end(t);}
}

namespace A {struct C{}; int* begin(C) {return 0;} int* end(C) {return 0;}}

int main()
{
    A::C c;
    for (auto e : c) (void)e; 
}