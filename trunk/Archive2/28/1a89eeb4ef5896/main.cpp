#include <iostream>
using namespace std;


struct A {
    const char* getString() const {return "A";}
};
struct B {
    friend ostream& operator<<(ostream&out, const B& rhs) {return out<<"B";}
};
struct C {
};


template<typename T, class valid = decltype(std::cout<<std::declval<T>().getString())>
ostream& operator<<(ostream &out, T&& value){return out<<value.getString(); }




int main() {
    A a;
    std::cout << a;
    B b;
    std::cout << b;
    C c;
    //std::cout << c; //error: no match for 'operator<<' (operand types are 'std::ostream {aka std::basic_ostream<char>} and 'C')    
}