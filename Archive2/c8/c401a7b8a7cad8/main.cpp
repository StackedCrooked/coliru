#include <array>
#include <stddef.h>
using std::array;
typedef ptrdiff_t Size;

    namespace detail {
        template< class Fixed_size_container >
        struct N_items_;

        template< class Item, Size n >
        struct N_items_
            < Item (&)[n] >
        { static Size constexpr count = n; };

        template< class Item, Size n >
        struct N_items_
            < array<Item, n> >
        { static Size constexpr count = n; };
    }  // namespace detail

    template< class Fixed_size_container >
    auto constexpr n_items()
        -> Size
    { return detail::N_items_<Fixed_size_container>::count; }

#include <iostream>
using namespace std;

auto main()
    -> int
{
    typedef int A[5];
    cout << n_items<A>() << endl;
}
