#include <type_traits>
using namespace std;

template<typename T> void foo(const T& whatever)
{
    static_assert(is_same<T, typename add_const<T>::type>(), "");
}

int main()
{
    foo<const int>(42);
}