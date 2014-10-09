#include <boost/any.hpp>
#include <iostream>
#include <string>
#include <functional>

struct ostreamable_any {
    ostreamable_any() = default;
    template<class T>ostreamable_any(T&&rhs):data(rhs),ostreamer([](std::ostream&o,const boost::any&v)->std::ostream&{return o<<boost::any_cast<T>(v);}){}
    friend std::ostream& operator<<(std::ostream&o,const ostreamable_any&rhs){return rhs.ostreamer(o,rhs.data);}
private:
    boost::any data;
    std::function<std::ostream&(std::ostream&,const boost::any&)> ostreamer;
};

int main(){
    ostreamable_any a = 5;
    std::cout << a << '\n';
}