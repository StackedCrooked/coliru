#include <iostream>

int f(int)
{
    return 0;
}

template<typename T>    
void Test(const T&)
{
    decltype(std::declval<T>()(std::declval<int>())) i1 = 1; // ok
    typename std::result_of<const T& (int)>::type i2 = 2; // compile error:
    // function returning a function
    // i think this means the same thing just as above，right?
}

int main()
{
    Test(f);
}
