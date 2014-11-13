#include <iostream>
#include <typeinfo>

using namespace std;

// a function (C++14 auto function return type deduction)
auto squareFunc(float x) { return x * x; }; 
// a function (C++11 explicit trailing return type)
auto squareFuncExplicitReturn(float x) -> float { return x * x; }; 
// a forward declaration for a function (C++11 trailing return type)
auto squareFuncForwardDeclared(float x) -> float; 
// define previously forward declared function
auto squareFuncForwardDeclared(float x) -> float { return x * x; }; 
// a lambda with no capture
auto squareLambda = [](float x) { return x * x; }; 
// a lambda with explicit trailing return
auto squareLambdaExplicitReturn = [](float x) -> float { return x * x; }; 
// an alias for a function pointer float -> float
using floatToFloat = auto (*)(float) -> float;
// a function that takes a function pointer float -> float
// can take any of the above as a parameter
auto applyPtr(floatToFloat f, float x) { return f(x); } 
// a generic lambda that applies any callable f to its argument x
auto applyLambda = [](auto f, auto x) { return f(x); };

int main() {
    auto show = [](auto name, auto value) { cout << typeid(value).name() << " " << name << " = " << value << "\n"; };
    #define SHOW(x) show(#x, x)

    auto f0 = float{};
    SHOW(f0);
    auto f1 = float{1};
    SHOW(f1);
    auto f2 = 1;
    SHOW(f2);
    auto f3 = 1.0;
    SHOW(f3);
    auto f4 = 1.0f;
    SHOW(f4);
    f4 = 1;
    SHOW(f4);
    
    SHOW(squareFunc(2.0f));
    
    floatToFloat squarePtr = squareFunc;
    SHOW(squarePtr(2.0f));
    
    squarePtr = squareLambda;
    SHOW(squarePtr(2.0f));
    
    squarePtr = squareLambdaExplicitReturn;
    SHOW(squarePtr(2.0f));
    
    SHOW(applyPtr(squareFunc, 2.0f));
    SHOW(applyPtr(squareLambda, 2.0f));
    SHOW(applyLambda(squareFunc, 2.0f));
    SHOW(applyLambda(squareLambda, 2.0f));
    
    #undef SHOW
}