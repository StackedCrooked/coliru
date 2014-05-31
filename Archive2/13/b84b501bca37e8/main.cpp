#include <type_traits>
#include <iostream>

using namespace std;

template<typename T>
typename enable_if<!is_integral<T>::value>::type foo(T x)
{
    cout << "general = " << x << endl;
}

template<typename T>
typename enable_if<is_integral<T>::value>::type foo(T x)
{
    cout << "integral = " << x << endl;
}

int main()
{
    foo(0.1);
    foo(0.2f);
    foo(3u);
    foo(4);
}
