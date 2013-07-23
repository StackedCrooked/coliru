#include <iostream>
#include <utility>
#include <vector>
#include <list>

using namespace std;

template<typename ...Ts>
int require(Ts ...);

struct random_access_iterator_check
{
    typedef char yes_type;
    typedef char (&no_type)[2];

    template <typename T> static no_type test(...);

    template <typename T>
    static yes_type test(int, T it = T{}, decltype(require
    (
        *it,
        ++it,
        it + 5,
        it - it,
        // etc
        1
    ))* =0);
};

template <typename T>
struct is_random_access_iterator : is_same
    <
        decltype(random_access_iterator_check::template test<T>(0)),
        random_access_iterator_check::yes_type
    >
{};

template<typename T>
void test()
{
    cout << is_random_access_iterator<T>::value << endl;
}
int main()
{
    test<int *>();
    test<vector<int>::iterator>();
    test<int>();
    test<list<int>::iterator>();
}