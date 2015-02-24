#include <iostream>
#include <string>
#include <type_traits>

template <typename CharT, typename Traits, typename Allocator>
void foo(const std::basic_string<CharT, Traits, Allocator>&)
{ std::cout << __PRETTY_FUNCTION__ << '\n'; }

inline void foo(const std::string& u) { std::cout << __PRETTY_FUNCTION__ << '\n'; foo<>(u); }
inline void foo(const std::wstring& u) { std::cout << __PRETTY_FUNCTION__ << '\n'; foo<>(u); }

void bar(const std::string&)
{}

int main()
{
  bar("abc");
  foo("def");
  foo(L"abc");
  foo(std::basic_string<unsigned char>{});
}