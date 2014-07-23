#include <type_traits>

template<class T>
struct foo
{
    static_assert(std::is_same<T, void>{}, "T is not void");
};

int main()
{
    std::conditional<true, int, foo<int>>::type x;
}