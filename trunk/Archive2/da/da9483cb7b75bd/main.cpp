// Maximum value the counter can hold
#define MAX_COUNT 64

// Used to store a number as the size of the structure
template<unsigned int n> struct Count { typedef bool (&type)[n]; };

// Used to overload functions while automatically selecting the right one based on the counter value
template<int n> struct cn : public cn<n-1> {};
template<> struct cn<0> {};

#ifdef TEMPLATED
template<typename T>
#endif
struct Test
{
    #define COUNT \
        ((sizeof(f(cn<MAX_COUNT + 1>())) / sizeof(bool)) - 1)
        
    static Count<1>::type f(cn<1>);
    
    /*
        f(cn<65>()) will 'call' f(cn<1>) and return a Count<1> with size 1
        -> count = 0;
    */
    static const int a = COUNT;
    static Count<COUNT + 2>::type f(cn<COUNT + 2>);
    
    /*
        now Count<2> f(cn<2>) is defined, so:
        f(cn<65>()) will 'call' f(cn<2>) and return a Count<2> with size 2
        -> count = 1;
    */
    static const int b = COUNT;
};

#ifdef TEMPLATED
typedef Test<int> N;
#else
typedef Test N;
#endif

#include <iostream>

int main()
{
#ifdef TEMPLATED
    std::cout << "Templated\n";
#else
    std::cout << "Non templated\n";
#endif
    std::cout << "a = " << N::a << "\n";
    std::cout << "b = " << N::b << "\n";
}