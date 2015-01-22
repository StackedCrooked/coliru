#include <cassert>
#include <type_traits>

template< typename get_x >
struct XY {
    get_x x;
    decltype( x() ) y;

    auto sum() { return x() + y; }
};

template< typename get_x >
XY< get_x > make_XY( get_x x, decltype( x() ) y )
    { return { x, y }; }

int main() {
    int x = 3;
    auto xy = make_XY( [&]{ return x; }, 4 );

    assert(xy.sum() == 7);

    auto xy2 = make_XY( [&]{ return x; }, 2 );
    assert(xy2.sum() == 5);

    static_assert(std::is_same<decltype(xy),decltype(xy2)>::value == false, "");
};
