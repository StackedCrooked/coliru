//#include <iostream>
#include <type_traits>

typedef double FuncType(double);

template <typename T>
struct Eval
{
    static const bool value = sizeof(T) == sizeof(int);
};

template <typename F>
void fun(const F& f, typename std::enable_if< Eval<F>::value >::type* = 0)
{

}

template <typename F>
void fun(F f, typename std::enable_if< std::is_same<F, FuncType*>::value >::type* = 0)
{

}

double Test(double d) { return d; }

int main(int argc, const char * argv[])
{
    fun(Test);

    // insert code here...
    //std::cout << "Hello, World!\n";
    return 0;
}

