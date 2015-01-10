#include <iostream>

template <typename T>
struct Base { 
    friend std::ostream& operator<<(std::ostream& os, Base const& ) {
        return os << "Base";
    }
};

struct Derived : Base<int> { };

struct Derived2 : Base<double> {
    friend std::ostream& operator<<(std::ostream& os, Derived2 const& ) {
        return os << "D2";
    }
};

struct D22 : Derived2 { };

int main()
{
    std::cout << Base<int>{} << std::endl;
    std::cout << Derived{} << std::endl;
    std::cout << Derived2{} << std::endl;
    std::cout << D22{} << std::endl;
}