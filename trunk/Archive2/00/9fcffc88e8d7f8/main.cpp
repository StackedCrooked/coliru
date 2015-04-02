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
    A::C c, arr[10];
    auto begin = range_access::begin(c), 
         end   = range_access::end(c);
    auto begin_arr = range_access::begin(arr), 
         end_arr   = range_access::end(arr);
    (void)begin, (void)end;(void)begin_arr, (void)end_arr;
}