#include <iostream>
#include <tuple>
#include <utility>
using namespace std;
 
    template<class Func, class Tuple, size_t...Is>
    void for_each_in_tuple(Func f, Tuple&& tuple, std::index_sequence<Is...>){
        using expander = int[];
        (void)expander { 0, ((void)f(std::get<Is>(std::forward<Tuple>(tuple))), 0)... };
    }
    
    template<class Func, class Tuple>
    void for_each_in_tuple(Func f, Tuple&& tuple){
        for_each_in_tuple(f, tuple, std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>::value>());
    }
 
class Lambda{
public: 
   template<class T>
   void operator()(T arg){ std::cout << arg << "; "; }
};
 
int main() {
    for_each_in_tuple(Lambda{}, std::make_tuple(1, 2.0f));
}
 