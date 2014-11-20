#include <string>
#include <utility>

template <typename Tag, typename... Args>
struct TagAlloc : std::allocator<Args...> {
    using std::allocator<Args...>::allocator;
};

template <typename Tag>
    using xstring = std::basic_string<char, std::char_traits<char>, TagAlloc<Tag, char> >;

#include <iostream>

int main()
{
    xstring<struct One> s1("one");
    xstring<struct Two> s2("two");

    std::cout << std::boolalpha << std::equal_to<xstring<struct One>>()(s1, "literal") << "\n";
    // not ok: std::cout << std::equal_to<xstring<struct One>>()(s2, s1) << "\n";
    // not ok: std::cout << std::equal_to<xstring<struct Two>>(s1, "literal") << "\n";
    // not ok: std::cout << std::equal_to<xstring<struct Two>>(s1, "literal") << "\n";
}
