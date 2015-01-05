#include <initializer_list>
#include <iostream>
#include <utility>

void operation()
{
    std::cout << "operation\n";
}

namespace detail
{

    template <std::size_t ... Is>
    void do_operation(std::index_sequence<Is...>)
    {
        static_cast<void>(std::initializer_list<std::size_t>{(static_cast<void>(operation()), Is)...});
    }

}

template <std::size_t N>
void do_operation()
{
    detail::do_operation(std::make_index_sequence<N>());
}

int main()
{
    do_operation<5>();
}
