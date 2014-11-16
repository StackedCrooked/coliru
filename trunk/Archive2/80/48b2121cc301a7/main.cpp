#include <utility>
#include <iostream>

namespace detail
{
    template <std::size_t... i>
    void foo( std::index_sequence<i...> )
    {
        int temp[sizeof...(i)];
        (void)std::initializer_list<int>{ (temp[i] = i)... };
        
        (void)std::initializer_list<bool>{ (std::cout << temp[i] << ", ")... };
        
    }
}

template <std::size_t dim>
void foo()
{
   detail:: foo( std::make_index_sequence<dim>() );
}

int main()
{
    foo<5>();
}