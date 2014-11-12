#include <iostream>
#include <array>


//namespace detail {
    template<typename T>
    struct a_initializer;
    
    template<>
    struct a_initializer<int> {
        using array_type = std::array<int, 5>;
        static constexpr std::array<int, 5> a {{1, 2, 3, 4, 5}};
    };
//}

//A.hpp
template<typename T>
class A {
public:
   // typedef typename detail::a_initializer<T>::array_type array_type;
   // static constexpr array_type a = detail::a_initializer<T>::a;
    static constexpr typename a_initializer<T>::array_type a = a_initializer<T>::a;
    constexpr A() {};
   // virtual ~A() {};
};



//B.hpp
class B final : public A<int> {
public:
     B();
    ~B();
};
//B.cpp
//template<>
//constexpr int A<int>::a[];

const a_initializer<int>::array_type a_initializer<int>::a = a_initializer<int>::a;

template<>
constexpr a_initializer<int>::array_type A<int>::a;

 B::B() {}
B::~B() {}

int main(){
    constexpr A<int> a;
 //   std::cout << sizeof(A<int>::a) << std::endl;
    std::cout << A<int>::a[2] << std::endl;
}