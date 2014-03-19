#include <iostream>

#include <boost/bind.hpp>
#include <boost/function.hpp>

struct S {
    S(const char *s) : s_(s) {}
    operator const char *() const {return s_;}
    
private:
    const char *s_;
};

int main() {
    S s("abc");
    boost::function<const char *()> f = boost::bind(&S::operator const char *, &s);  
    std::cout << f();
}