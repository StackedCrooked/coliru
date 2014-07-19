#include <type_traits>

int main()
{
    static_assert(std::is_convertible<int, short>{}, "int is not convertible to short");
    static_assert(std::is_convertible<int, void>{}, "int is not convertible to void");
}