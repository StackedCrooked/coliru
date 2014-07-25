#include <type_traits>
#include <cstddef>

template<typename T> constexpr std::size_t array_counter(std::size_t x)
{
    static_assert(std::is_array<T>::value, "ARRAY_COUNT called on non-array");
	return x;
}
#define ARRAY_COUNT(array) array_counter<decltype(array)>(sizeof(array)/sizeof(array[0]))

int main()
{
    const char** a = 0;
    const char* b[] = { "test" };
    
    static_assert (ARRAY_COUNT(b) == 1, "worked");
    ARRAY_COUNT(a);
}
