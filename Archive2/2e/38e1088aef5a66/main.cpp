#include <iostream>

#if 1
template<class T>
T Connect(typename std::enable_if<std::is_same<bool, bool>::value, T>::type func)
{
    return func;
}

#else

template<class T>
typename std::enable_if<std::is_same<bool, bool>::value, T>::type Connect(T func)
{
    return func;
}

#endif

int main()
{
    Connect([]{});
}
