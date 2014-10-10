#include <iostream>
#include <tuple>
#include <typeinfo>
using namespace std;

template<class...T>
struct InvTuple;

template<class T1, class...T>
struct InvTuple < T1, T... >
{
    template<class... U>
    using doInvert = typename InvTuple<T...>::template doInvert < T1, U... >;

    using type = doInvert<>;
};

template<>
struct InvTuple <>
{
    template<class... U>
    using doInvert = tuple<U...>;

    using type = doInvert < > ;
};

int main()
{
    InvTuple<int,char,bool> obj;
    InvTuple<int,char,bool>::type obj2;
    cout << typeid(obj).name() << endl;
    cout << typeid(obj2).name() << endl;
    
}