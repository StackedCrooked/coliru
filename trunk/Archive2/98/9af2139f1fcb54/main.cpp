#include <type_traits>

void foo() {}

int main()
{
    static_assert( std::is_function<decltype( foo )>(), "" );
    auto&& what_is_this = foo;
    using behind_the_double_ampersand = std::remove_reference<decltype( what_is_this )>::type;
    static_assert( std::is_function<behind_the_double_ampersand>(), "" );
    static_assert( std::is_pointer<std::remove_reference<decltype( &foo )>::type>(), "" );
}