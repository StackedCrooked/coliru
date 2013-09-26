#include <iostream>
#include <memory>

template <typename T>
void func1(T& value)
{
    std::cout << "passed 1 ..." << std::endl;
}

template <template <typename> class T, typename U>
void func2(T<U>& value)
{
    std::cout << "passed 2 ..." << std::endl;
}

int main()
{
    std::auto_ptr<int> a;
    const std::auto_ptr<int> ca;

    // case 1: using func1
    func1(a);  // OK
    func1(ca); // OK

    // case 2: using func2
    func2(a);  // OK
    func2(ca); // Error

    return 0;
}
