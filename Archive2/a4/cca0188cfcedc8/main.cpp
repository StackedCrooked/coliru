#include <string>
#include <iostream>

enum class MF : int {
    ZERO = 0,
    ONE = 1,
    TWO = 2
};

// --------- Variadic Template -------------
template<MF mf, typename... E>
class Var{
public:
    Var(std::string msg){
        std::cout << "Generic Var constructor: " << msg << std::endl;
    }

};

// --------- Variadic Template Specialization -------------
template<typename... E>
class Var<MF::TWO, E...>{
public:
    Var(std::string msg){
        std::cout << "Specialized Var constructor: " << msg << std::endl;
    }
};

int main() {
  Var<MF::TWO> v("hello!"); 
}