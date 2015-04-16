#include <iostream>
#include <type_traits>
using namespace std;

enum test {A='A',B='B',C='C'};

template <test E, typename Enable = void>
struct SomeClass
{
    void foo(){cout << "Primary" << endl;}
};

template <test E>
struct SomeClass<E, enable_if_t<E==A>>
{
    void foo()
    {
        cout << (char)E<<endl;
    }
};

template <test E>
struct SomeClass<E, enable_if_t<E==B>>
{
    void foo()
    {
        cout << (char)E<<endl;
    }
};

int main()
{
    SomeClass<A>{}.foo();
    SomeClass<B>{}.foo();
    SomeClass<C>{}.foo();
    return 0;
}