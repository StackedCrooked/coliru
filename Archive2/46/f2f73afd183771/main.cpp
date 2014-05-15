#include <iostream>
#include <vector>

enum X
{
    CL_DEVICE_TYPE_GPU,
    CL_DEVICE_NAME
};

struct Device
{
    template<X x>
    char const* getInfo()
    {
        return "hello world";
    }
};

template <typename T>
struct Foo {
    void bar();

    std::vector<Device> devices;
};

template<typename T>
void Foo<T>::bar() {
    // Fails to compile:  error: expected expression
    std::cout << devices[0].getInfo<CL_DEVICE_NAME>() << std::endl;
    // Also works
    Device &mydevice = devices[0];
    std::cout << mydevice.getInfo<CL_DEVICE_NAME>() << std::endl;
}

int main() {
    Foo<double> foo = Foo<double>();    
    foo.bar();    
    return 0;
}