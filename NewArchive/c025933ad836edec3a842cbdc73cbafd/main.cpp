#include <type_traits>

static_assert(!std::is_class<int>::value, "Test");

int main()
{
}