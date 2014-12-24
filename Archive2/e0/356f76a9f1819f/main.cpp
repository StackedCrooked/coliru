template<typename T, typename U>
class pair
{
    T t;
    U u;
};

struct copy_and_move {};
struct move_only { move_only(move_only&&) = default; move_only& operator=(move_only&&) = default; };

#include <iostream>
#include <type_traits>

int main()
{
    using p0 = pair<copy_and_move, move_only>;
    std::cout << std::boolalpha << std::is_nothrow_move_assignable<p0>::value << "\n";
}