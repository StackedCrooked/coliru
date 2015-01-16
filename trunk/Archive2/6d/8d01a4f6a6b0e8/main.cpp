#include <iostream>

template<class T>
struct Defaults{};

template<>
struct Defaults<int>{
   static constexpr int value1=-50;
   static constexpr int value2=50;
};
template<>
struct Defaults<float>{
    static constexpr float value1=-0.5;
    static constexpr float value2=0.5;
};

template<class T>
class Foo{
public:
    Foo(T value1 = Defaults<T>::value1, T value2 = Defaults<T>::value2)
        : value1_(value1), value2_(value2){ }
    
    T value1_, value2_;
};

int main()
{
    Foo<float> test;
    std::cout << test.value1_ << " " << test.value2_ << '\n';

    Foo<int> test2;
    std::cout << test2.value1_ << " " << test2.value2_;
}