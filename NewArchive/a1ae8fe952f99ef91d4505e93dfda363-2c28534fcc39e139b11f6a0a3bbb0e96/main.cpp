#include <iostream>
#include <utility>
#include <vector>
#include <list>

using namespace std;

template<typename ...Ts>
int requires(Ts ...);

template<bool> struct dummy{ typedef int type;};

struct regular_check
{
    typedef char yes_type;
    typedef char (&no_type)[2];

    template <typename T> static no_type test(...);

    template <typename T>
    static yes_type test( typename dummy<false && []
    {
        //T x = T{};

        /*T{};
        T{x};
        T{ x = x };

        bool{ x == x };
        bool{ x != x };

        bool{ x < x };
        bool{ x <= x };
        bool{ x > x };
        bool{ x >= x };*/
    }>::type);
};

template <typename T>
struct is_regular
{
    enum
    {
        value = is_same
        <
            decltype(regular_check::template test<T>(0)),
            regular_check::yes_type
        >::value
    };
};

template<typename T>
void test()
{
    cout << is_regular<T>::value << endl;
}
int main()
{
    test<int>();
    test<list<int>>();
    test<vector<int>>();
    test<int *>();
    test<list<int>::iterator>();
}