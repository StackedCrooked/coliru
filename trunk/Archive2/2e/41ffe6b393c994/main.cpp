#include <boost/logic/tribool.hpp>

#include <vector>

int f(int a, int b, int c);

template<typename T>
struct print_type;

int main()
{
    boost::logic::tribool a;
    bool b;
    
    a=b;
    
    std::vector<bool> bs;
    a=bs[0];
    return 0;
}