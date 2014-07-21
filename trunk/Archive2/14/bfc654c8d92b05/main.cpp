#include <iostream>

int f(int)
{
    return 0;
}

struct foo {
    double operator () (int) const { return 0; }
};

template<typename T>    
void Test(const T&)
{
    decltype(std::declval<T>()(std::declval<int>())) i1 = 1;
    typename std::result_of<T>::type i2 = 2;
    // silence "unused variable" warnings.
    (void)i1;
    (void)i2;
}

int main()
{
    Test(f);
    Test(foo());
}
