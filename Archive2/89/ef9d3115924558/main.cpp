#include <iostream>

template <typename T>
struct XYZ
{
    // remove following two lines to make the code compile
    XYZ (XYZ const & rhs) = delete; 
    XYZ (XYZ && rhs) = delete; 
    T i;
    XYZ (T i):i(i)
    {
    }
};

template <typename T>
XYZ<T> make_XYZ (T && i)
{
    return { std::forward<T>(i) };
}

int main ()
{
    auto&& x = make_XYZ(1);
    std::cout << x.i << std::endl;
}