#include <iostream>
#include <utility>

template<typename T> void test(T) { std::cout << __PRETTY_FUNCTION__ << std::endl; }


template<typename Head, typename Tail>
struct List
{
    List() : head(), tail() {}    
    List(Head head, Tail tail) : head(head), tail(tail) {}    
    Head head;
    Tail tail;
};


template<typename Head, typename Tail>
auto MakeList(Head head, Tail tail)
{
    return List<Head, Tail>(head, tail);
}




template<typename A, typename B>
auto operator+(A a, B b);

template<typename A, typename B, typename C>
auto operator+(List<A, B> l, C c);

template<typename A, typename B, typename C>
auto operator+(A a, List<B, C> l);

template<typename A, typename B, typename C, typename D>
auto operator+(List<A, B> ab, List<C, D> cd);



template<typename A, typename B>
auto operator+(A a, B b)
{
    return List<A, B>(a, b);
}

template<typename A, typename B, typename C>
auto operator+(List<A, B> l, C c)
{
    return MakeList(l.head, MakeList(l.tail, c));
}


template<typename A, typename B, typename C>
auto operator+(A a, List<B, C> l)
{
    return MakeList(MakeList(a, l.head), l.tail);
}

template<typename A, typename B, typename C, typename D>
auto operator+(List<A, B> ab, List<C, D> cd)
{
    return (ab + cd.head) + cd.tail;
}


struct A {} a;
struct B {} b;
struct C {} c;
struct D {} d;
struct E {} e;
struct F {} f;
struct G {} g;


int main()
{   
    test(a + b);
    test(a + b + c);
    test(a + b + c + d);
    test(a + b + c + d + e);
    test(a + b + c + d + e + f);
    test(a + b + c + d + e + f + g);
    std::cout << std::endl;
    
    
    test(a + b);
    test(a + (b + c));
    test(a + (b + (c + d)));
    test(a + (b + (c + (d + e))));
    test(a + (b + (c + (d + (e + f)))));
    test(a + (b + (c + (d + (e + (f + g))))));
    std::cout << std::endl;
}


