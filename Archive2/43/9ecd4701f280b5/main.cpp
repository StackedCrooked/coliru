#include <iostream>

template<int I>
struct Foo
{
    Foo() = default;
    
    static const int myint = I;
    static int get();
    
    /* How do you define this? */
    template<typename T>
    static void something();
};


// Simple
template<int I>
int Foo<I>::get()
{
    return myint;
}

/*      Foo arg   Extra arg 
 *         v           v   */
template<int I,   typename T>
void Foo<I>::something()
{
    std::cout << "here\n";
}


int main(void)
{
    Foo<5> f{};
    std::cout << f.get() << std::endl;

    /*          Anything  */
    f.something<float>();
}   
