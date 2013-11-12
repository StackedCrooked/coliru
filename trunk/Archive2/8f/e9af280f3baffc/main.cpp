//#include <initializer_list>
#include <iterator>
#include <utility>
#include <cassert>
#include<array>
#include<iostream>
#include<boost/array.hpp>
/*
std::pair<double, double> to_pair(std::initializer_list<const double> init)
{
    return std::pair<double, double>(*init.begin(), *std::next(init.begin()) );
}*/
std::pair<double, double> to_pair_from_array(std::array<double, 2> init){
    return std::pair<double, double>(init[0], init[1]);
}

std::pair<double, double> to_pair_from_array(double z, std::array<double, 2> init){
    return std::pair<double, double>(init[0] + z, init[1] + z);
}

int main()
{
    using namespace std;
    std::pair<double, double> p = to_pair_from_array({1.,2.}); // ok
    std::pair<double, double> p2 = to_pair_from_array(3.,{1.,2.});
//    auto p2 = to_pair_from_array({1.,2.,3.}); // compile error, but ok
    cout << p.first << endl;
}
