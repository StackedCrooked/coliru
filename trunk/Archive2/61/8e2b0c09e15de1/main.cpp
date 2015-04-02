#include <initializer_list>

int main()
{
    constexpr auto l = std::initializer_list<int> {};
    static_assert( l.size() == 0, "" );
}