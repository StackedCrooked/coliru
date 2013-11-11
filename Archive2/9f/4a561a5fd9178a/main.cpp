#include <initializer_list>
#include <iostream>
constexpr double fun(std::initializer_list<double> init){
    return init.size()==2?2.2222:3.3333;
}
constexpr double gun(std::initializer_list<double> init){
    static_assert(init.size() == 2, ""); // not ok, "init is not a constant expression
    return 2.;
}
constexpr double hun(constexpr std::initializer_list<double> init){ // not ok, "a parameter canot be declared constexpr
    static_assert(init.size() == 2, "");
    return 2.;
}


using namespace std;
int main(){
    std::cout << fun({1.,2.}) << std::endl; // prints 2.2222, ok!
    std::cout << fun({1.,2.,3.}) << std::endl; // prints 3.3333, ok!
    static_assert(fun({1.,2.})==2.2222, ""); // ok
    static_assert(fun({1.,2.,3.})==2.2222, ""); // ok, compile time fail
}
