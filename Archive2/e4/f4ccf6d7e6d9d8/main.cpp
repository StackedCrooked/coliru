#include <iostream>
#include <string>
#include <vector>
#include "boost/variant.hpp"

struct A {};

void use(int x) { std::cout << "int = " << x << std::endl; }
void use(const std::string& x) { std::cout << "string = " << x << std::endl; }
void use(const A&) { std::cout << "class A" << std::endl; }

typedef boost::variant<int,std::string,A> m_types;

class use_func : public boost::static_visitor<>
{
public:
    template <typename T>
    void operator()( T & operand ) const
    {
        use(operand);
    }
};
int main()
{
    std::vector<m_types> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(std::string("hello"));
    vec.push_back(A());
    for (int i=0;i<4;++i)
        boost::apply_visitor( use_func(), vec[i] );
    return 0;
}