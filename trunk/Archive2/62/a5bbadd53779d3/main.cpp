#include <type_traits>

template<class T>
struct incomplete;

int main()
{
    std::conditional<true, incomplete<int>, void>::type* p = nullptr;
}