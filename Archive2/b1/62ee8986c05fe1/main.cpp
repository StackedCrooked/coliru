#include <iterator>

namespace range_access {
    using std::begin;
    using std::end  ;
    
    template <typename T>
    auto adl_begin( T&& t )
      -> decltype(begin(std::forward<T>(t))) {
        return    begin(std::forward<T>(t));
    }
    template <typename T>
    auto adl_end( T&& t )
      -> decltype(end(std::forward<T>(t))) {
        return    end(std::forward<T>(t));
    }
}

namespace A {struct C{}; int* begin(C) {return 0;} int* end(C) {return 0;}}

int main()
{
    A::C c, arr[10];
    auto begin = range_access::adl_begin(c), 
         end   = range_access::adl_end(c);
    auto begin_arr = range_access::adl_begin(arr), 
         end_arr   = range_access::adl_end(arr);
    (void)begin, (void)end;(void)begin_arr, (void)end_arr;
}