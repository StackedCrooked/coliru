#include <iostream>
#include <utility>
#include <string>
 
#include <unordered_map>

class A {
public:
    A(const std::string& a, int b) {
        std::cout<<"Constructing " << a << b << "\n";
        a_ = a;
    }
    std::string operator()(){return a_;}
    std::string a_;
};

int main()
{
    std::unordered_map<std::string, A> m;
 
    m.emplace(std::make_pair("a", A("a",1)));

    // uses pair's piecewise constructor (overload 6)
    m.emplace(std::piecewise_construct,
              std::forward_as_tuple("a"),
              std::forward_as_tuple("ccd",1));
 
    for (const auto &p : m) {
        std::cout << p.first << " => " << p.second.a_ << '\n';
    }
}