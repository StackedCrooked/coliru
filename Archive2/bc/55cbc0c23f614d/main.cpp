#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>
#include <iostream>

int main() {
    boost::tuple<std::string, float> var1 = boost::make_tuple("test", 123.0f);

    std::string s1 = boost::get<0>(var1);
    float f1       = boost::get<1>(var1);
    
    std::cout << "var1: " << var1 << "\n";
    std::cout << "s1: "   << s1 << "\n";
    std::cout << "f1: "   << f1 << "\n";
}