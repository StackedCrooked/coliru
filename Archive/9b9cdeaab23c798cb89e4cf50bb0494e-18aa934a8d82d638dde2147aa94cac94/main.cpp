#include <memory>


enum Flag
{
    A = 1 << 0,
    B = 1 << 1,
    C = 1 << 2,
};


struct OptionA { void use_a(){} };
struct OptionB { void use_b(){} };
struct OptionC { void use_c(){} };


template<typename T, bool> struct Select : T { };
template<typename T> struct Select<T, false> { };


template<int N>
struct Options : Select<OptionA, N & A>,
                 Select<OptionB, N & B>,
                 Select<OptionC, N & C>
{
};


int main()
{
    Options<A> opt1;
    opt1.use_a();
    
    Options<A | B> opt2;
    opt2.use_a();
    opt2.use_b();
    
    Options<A | C> opt3;
    opt3.use_a();
    opt3.use_b();
    opt3.use_c();
}