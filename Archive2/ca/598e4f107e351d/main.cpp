#include <cstdio>

template<class M> struct Match          { typedef M type; };
template<class V> struct Yield          { typedef V type; V var; };
template<class V, class M> struct Combo { typedef M type; V var; };

template<class Y, class M> struct Arg
{
    typedef typename M::type match;
};


template<class V> struct YM : Arg< Yield<V>,      Match<V>      > {};
template<class V> struct YY : Arg< Yield<V>,      Yield<V>      > {};
template<class V> struct CC : Arg< Combo<V,char>, Combo<char,V> > {};

template<class V> struct YMi : Arg< Yield<int>,      Match<V>      > {};
template<class V> struct YYi : Arg< Yield<int>,      Yield<V>      > {};
template<class V> struct CCi : Arg< Combo<int,char>, Combo<char,V> > {};


template<class T> void operator , (typename T::match, T)
{
    printf("called %s\n", __PRETTY_FUNCTION__);
}

int main()
{
    int(), YM<int>(); // шаблонный
    int(), YY<int>(); // шаблонный
    int(), CC<int>(); // шаблонный

    void(), YM<void>(); // проверяется шаблонный, выполняется дефолтный
    //void(), YY<void>();
    void(), CC<void>();

    int(), YMi<int>(); // шаблонный
    int(), YYi<int>(); // шаблонный
    int(), CCi<int>(); // шаблонный

    void(), YMi<void>(); // проверяется шаблонный, выполняется дефолтный
    //void(), YYi<void>();
    void(), CCi<void>(); // проверяется шаблонный, выполняется дефолтный
}