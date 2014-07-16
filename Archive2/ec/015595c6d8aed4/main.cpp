#include <iostream>
#include <array>
#include <memory>
#include <vector>

template <typename T, typename = void>
struct hasNullComparator : std::false_type {};

template <typename T>
struct hasNullComparator<T,
typename std::enable_if<std::is_same<decltype(T::compareToNull()), bool>::value>::type>
: std::true_type {};

struct Foo {
    static bool compareToNull() { return true; }
};

static_assert(hasNullComparator<Foo>::value, "");
static_assert(!hasNullComparator<int>::value, "");

int main() {
	return 0;
}