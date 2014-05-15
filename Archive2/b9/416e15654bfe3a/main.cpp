struct Device
{
    template<int x>
    char const* getInfo()
    {
        return "hello world";
    }
};

template <typename T>
struct Foo {
    void bar();

    Device devices[2];
};

template<typename T>
void Foo<T>::bar() {
    // Fails to compile:  error: expected expression
    devices[0].getInfo<0>();
    // Also works
    Device &mydevice = devices[0];
    mydevice.getInfo<0>();
}

int main() {
    Foo<double> foo = Foo<double>();    
    foo.bar();    
    return 0;
}