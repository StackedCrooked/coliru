#include <iterator>
#include <type_traits>
#include <string>

using namespace std;

template <typename I>
using ValueType = typename std::iterator_traits<I>::value_type;

template <typename I0, typename I1>
void f(I0 x, I1 y)
{
    static_assert(is_convertible<ValueType<I0>, ValueType<I1>>::value, "ValueType<I0> is not convertible to ValueType<I1>!");
    static_assert(is_convertible<ValueType<I1>, ValueType<I0>>::value, "ValueType<I1> is not convertible to ValueType<I0>!");
    static_assert(is_same<ValueType<I0>, ValueType<I1>>::value, "Iterator value types are not the same!");
}

int main()
{
    int a[1];
    double b[1];
    string c[1];
    f(begin(a), begin(a));
    f(begin(a), begin(b));
    f(begin(a), begin(c));
}
