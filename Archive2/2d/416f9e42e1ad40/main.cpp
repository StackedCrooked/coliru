#include <tuple>

template <int... I>
struct ints {};

template <int... Init>
void f(ints<Init..., sizeof...(Init)>) {}

int main()
{
    f(ints<0, 1, 2, 3>());
}
