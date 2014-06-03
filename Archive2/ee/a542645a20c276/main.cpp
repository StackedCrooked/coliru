enum { a };

#include <type_traits>

enum { A };

template <class T>
struct foo {
    static const auto value = A;
};

template<class T>
const decltype (foo<T>::value) foo<T>::value;

int main()
{
    static constexpr auto r = foo<int>::value;
}
