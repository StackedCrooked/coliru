#include <iostream>
using std::cout;
using std::endl;

enum class FooBar
{
    Foo,
    Bar,
    Size
};

template<typename T>
auto size()
{
    return static_cast<typename std::underlying_type<T>::type>(T::Size);
}

int main(int argc, char* argv[])
{
    cout << size<FooBar>() << endl;
    return 0;
}