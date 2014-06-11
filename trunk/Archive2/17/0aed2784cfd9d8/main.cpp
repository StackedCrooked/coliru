#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <type_traits>

typedef void (*FunctionType)(int);

template<class T>
constexpr bool HasFunctionTest(decltype(&T::Foo)) {
    return std::is_same<decltype(&T::Foo), FunctionType>::value;
}

template<class T>
constexpr bool HasFunctionTest(...) {
    return false;
}

template<class T>
constexpr bool HasFunction() {
    return HasFunctionTest<T>(nullptr);
}

struct WithFunction {
    static void Foo(int);
};

struct WithNonstaticFunction {
    void Foo(int);
};

struct WithWrongFunction {
    void Foo(double);
};

struct WithoutFunction {
};

int main()
{
    std::cout
        << HasFunction<WithFunction>() << " " 
        << HasFunction<WithNonstaticFunction>() << " " 
        << HasFunction<WithWrongFunction>() << " " 
        << HasFunction<WithoutFunction>() << "\n";  
}
