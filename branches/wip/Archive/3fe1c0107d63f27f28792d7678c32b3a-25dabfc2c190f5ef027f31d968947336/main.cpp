template<class T1>
struct A
{
    template<class T2>
    struct B
    {
        static A<T1>::B f;
        static typename A<T2>::template B<T1> g;
    };
};

template<class T1>
template<class T2>
typename A<T2>::template B<T1> // ok, typename/template required
    A<T1>::B<T2>::g;

template<class T1>
template<class T2>
A<T1>::B // clang/gcc accept, msvc rejects missing typename
    A<T1>::B<T2>::f;


int main()
{
}
