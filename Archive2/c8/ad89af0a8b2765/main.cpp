#include <cstddef>
#include <utility>
 
template <size_t... Indices>
void foo(std::index_sequence<Indices...>)
{
}

int main()
{
    foo(std::make_index_sequence<3>{});
}