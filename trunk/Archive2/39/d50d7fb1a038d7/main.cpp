#include <iostream>
#include <vector>

enum X
{
    CL_DEVICE_TYPE_GPU,
    CL_DEVICE_NAME
};

namespace cl
{
    struct Device
    {
        template<X x>
        char const* getInfo()
        {
            return "hello world";
        }
    };
    
    struct Platform
    {
        static void get(std::vector<Platform>* p)
        {
            static std::vector<Platform> platforms;
            *p = platforms;
        }
        
        void getDevices(X, std::vector<Device>* p)
        {
            static std::vector<Device> devices;
            *p = devices;
        }
    };
}

template <typename T>
class Foo {
    public:
    std::vector<cl::Platform> platforms;
    std::vector<cl::Device> devices;    
    Foo();   
    void bar();
};

template<typename T>
Foo<T>::Foo() {      
    cl::Platform::get(&platforms);
    platforms[0].getDevices(CL_DEVICE_TYPE_GPU, &devices);
}

template<typename T>
void Foo<T>::bar() {
    // Fails to compile:  error: expected expression
    //std::cout << devices[0].getInfo<CL_DEVICE_NAME>() << std::endl;
    // Works
    std::cout << this->devices[0].getInfo<CL_DEVICE_NAME>() << std::endl;
    // Also works
    cl::Device &mydevice = devices[0];
    std::cout << mydevice.getInfo<CL_DEVICE_NAME>() << std::endl;

}

int main() {
    Foo<double> foo = Foo<double>();    
    foo.bar();    
    return 0;
}