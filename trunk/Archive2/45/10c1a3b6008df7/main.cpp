#include<iostream>


template <typename T, typename R, typename... Args>
R call(R (T::*fn)(Args...), T *t, Args&&... args) {
    return ((*t).*fn)(std::forward<Args>(args)...);    
}

class Calculator
{
    public:
    template<typename T>
    auto add(T&& a, T&& b) -> decltype(std::forward<T>(a) + std::forward<T>(b))
    {
        return std::forward<T>(a) + std::forward<T>(b);
    }
};

int main() {
    Calculator *calculator = new Calculator();
    int* a = new int(2);    
    int* b = new int(4);

    // compiles
    int res1 = calculator->add(*a, *b);    

    // does not compile!
    int res2 = call(&Calculator::add<decltype(*a)>, calculator, *a, *b);    

    std::cout<<res1<<"  "<<res2<<std::endl;

    return 0;
}


