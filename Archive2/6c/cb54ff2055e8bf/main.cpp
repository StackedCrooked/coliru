#include <string>
#include <vector>
#include <iostream>
#include <utility>

    template<class T, size_t Size, size_t... sizes>
    struct multi_array {
      T raw[Size];
      constexpr size_t size() { return Size; }
      constexpr bool empty() { return false; }
      constexpr T* data() { return raw; }
      constexpr T const* data() const { return raw; }
      constexpr T* begin() { return raw; }
      constexpr T const* begin() const { return raw; }
      constexpr T* end() { return raw+Size; }
      constexpr T const* end() const { return raw+Size; }
      constexpr T& front() { return raw[0]; }
      constexpr T const& front() const { return raw[0]; }
      constexpr T& back() { return raw[Size-1]; }
      constexpr T const& back() const { return raw[Size-1]; }
    };
    template<class T, size_t... sizes>
    struct multi_array<T, 0, sizes...> {
      struct {} raw;
      constexpr size_t size() { return 0; }
      constexpr bool empty() { return true; }
      constexpr T* data() { return nullptr; }
      constexpr T const* data() const { return nullptr; }
      constexpr T* begin() { return nullptr; }
      constexpr T const* begin() const { return nullptr; }
      constexpr T* end() { return nullptr; }
      constexpr T const* end() const { return nullptr; }
    };
    template<class T, size_t Size, size_t SizeNext, size_t... sizes>
    struct multi_array<T,Size,SizeNext,sizes...> {
      using value_type = multi_array<T, SizeNext,sizes...>;
      value_type raw[Size];
      constexpr size_t size() { return Size; }
      constexpr bool empty() { return false; }
      constexpr value_type* data() { return raw; }
      constexpr value_type const* data() const { return raw; }
      constexpr value_type* begin() { return raw; }
      constexpr value_type const* begin() const { return raw; }
      constexpr value_type* end() { return raw+Size; }
      constexpr value_type const* end() const { return raw+Size; }
      constexpr value_type& front() { return raw[0]; }
      constexpr value_type const& front() const { return raw[0]; }
      constexpr value_type& back() { return raw[Size-1]; }
      constexpr value_type const& back() const { return raw[Size-1]; }
    };

int main()
{
    multi_array<int, 3,2> foo = {{ {{0,1}}, {{0}}, {{1,2}} }};
    for (auto&& a:foo)
        for (auto&& x:a)
            std::cout << x << '\n';
}