#include <boost/variant.hpp>
using boost::variant;
using boost::get;

#include <cassert>
#include <vector>
#include <iostream>
#include <string>
using std::vector;

struct VariantVectorPrinter : public boost::static_visitor<> {
#if 0
    void operator()(int &value) const {
        std::cout << value << std::endl;
    }
    void operator()(double &value) const {
        std::cout << value << std::endl;
    }
    void operator()(std::string &value) const {
        std::cout << value << std::endl;
    }
#endif
    template<class T>
    void operator()(T &value) const {
        std::cout << value << std::endl;
    }
    void operator()(std::string &value) const {
        std::cout << '"' << value << '"' << std::endl;
    }
};

int main() {
    vector< variant<int, double, std::string> > v;
    v.push_back(22);
    v.push_back(0.5);
    v.push_back(33);
    v.push_back("hello");
    
    for (auto elem : v) 
        boost::apply_visitor(VariantVectorPrinter(), elem);
    
    
    assert(get<int>(&v.at(0)) != 0);
    assert(get<double>(&v.at(0)) == 0);
    
    assert(get<int>(&v.at(1)) == 0);
    assert(get<double>(&v.at(1)) != 0);
    
    assert(get<int>(&v.at(2)) != 0);
    assert(get<double>(&v.at(2)) == 0);
    
    std::cout << "all tests passed" << std::endl;
}
    