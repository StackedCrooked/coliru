#include <type_traits>

template<typename T>
typename std::enable_if<!std::is_fundamental<T>::value, unsigned int >::type
myFunction(T myelement)
{
    myelement->func();
    return 2;
}

void myFunction(unsigned int myelement)
{
}

int main()
{
    myFunction(2);
}
