#include <initializer_list>
#include<map> //for pair
#include<iterator> // for next
#include<cassert> // for assert
#include <iostream>
constexpr bool is_pair(std::initializer_list<double> init){
    return init.size()==2?true:false;
}
std::pair<double, double> to_pair(std::initializer_list<double> init){
    return std::pair<double, double>(*init.begin(), *std::next(init.begin()) );
}

std::pair<double, double> to_pair_runtime_check(std::initializer_list<double> init){
    assert(init.size() == 2);
    return std::pair<double, double>(*init.begin(), *std::next(init.begin()) );
}

std::pair<double, double> to_pair_compile_check(std::initializer_list<double> init){
    return init.size()==2?std::pair<double, double>(*init.begin(), *std::next(init.begin()) ):throw 0;
}

constexpr std::pair<double, double> to_pair_compile_check_ce(std::initializer_list<double> init){
    return init.size()==2?std::pair<double, double>(*init.begin(), *std::next(init.begin()) ):throw 0;
    // ^^^ not ok, because begin is not a const expr
}


using namespace std;
int main(){
    std::cout << is_pair({1.,2.}) << std::endl; // prints 1, ok!
    std::cout << is_pair({1.,2.,3.}) << std::endl; // prints 0, ok!
    auto p1 = to_pair({1.,2.}); // ok
    auto p2 = to_pair({1.,2.,3.}); // ok, but it can be logically better

    auto p3 = to_pair_runtime_check({1.,2.}); // ok
//    auto p4 = to_pair_runtime_check({1.,2.,3.}); // ok, runtime assert fails, so logically ok but it would be better at compile time

    auto p5 = to_pair_compile_check({1.,2.}); // ok
//    auto p6 = to_pair_compile_check({1.,2.,3.}); // ok, runtime assert fails

}
