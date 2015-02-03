#include <iostream>
#include <type_traits>

template <typename T1>
class B1 {};

template <typename T1>
class B2: public B1<T1> {};

template <typename T1, typename T2>
class C;

template <typename T1, template <typename> class BN, typename T2>
class C<T1, BN<T2> >
{
    static_assert(std::is_base_of<B1<T2>, BN<T2>>{}, "!");
public:
    C() {
        // do sth.
    }
};

template <typename T1, typename T2>
int getVal(C<T1, B2<T2> >& b2) {
    return 2;
}

template <typename T1, typename T2>
int getVal(C<T1, B1<T2> >& b1) {
    return 1;
}

template <typename T1, template <typename> class BN, typename T2>
auto doSomething(C<T1, BN<T2> >& c)
    -> typename std::enable_if<std::is_base_of<B1<T2>, BN<T2>>{}, int>::type
{
    return getVal(c);
}

int main()
{
    C<int, B1<int> > c1;
    C<int, B2<int> > c2;
    std::cout << doSomething(c1); // output 1
    std::cout << doSomething(c2); // output 2
}
