#include <iostream>
#include <map>
#include <string>

class Foo
{
private:
    std::map<std::string, long long int> libFunctions;

public:
    Foo() {}
    ~Foo(void) {}

    void putInMap(const std::string& name, long long int val)
    {
        libFunctions[name] = val;
    }

    template<typename FunctionPointerType>
    FunctionPointerType getFunctionPtr(std::string functionName);
};

template<typename FunctionPointerType>
FunctionPointerType Foo::getFunctionPtr(std::string functionName)
{
    return reinterpret_cast<FunctionPointerType>(this->libFunctions[functionName]);
}

int main()
{
    Foo f;
    f.putInMap("hello", 1);
    f.putInMap("world", 2);
    auto one = reinterpret_cast<long long int>(f.getFunctionPtr<int(*)()>("hello"));
    auto two = reinterpret_cast<long long int>(f.getFunctionPtr<double(*)(int, char)>("world"));
    std::cout << one << "," << two;
}