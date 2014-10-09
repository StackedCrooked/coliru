#include <boost/any.hpp>
#include <iostream>
#include <string>
#include <functional>

struct ostreamable_any {
    ostreamable_any() : data() {}
    ostreamable_any(const ostreamable_any&rhs):data(rhs.data),ostreamer(rhs.ostreamer){}
    ostreamable_any(ostreamable_any&rhs):data(rhs.data),ostreamer(rhs.ostreamer){}
    ostreamable_any(ostreamable_any&&rhs):data(std::move(rhs.data)),ostreamer(std::move(rhs.ostreamer)){}
    template<class T>ostreamable_any(T&&rhs):data(rhs),ostreamer([](std::ostream&o,const boost::any&v)->std::ostream&{return o<<boost::any_cast<T>(v);}){}
    ostreamable_any&operator=(const ostreamable_any&rhs){data=rhs.data;ostreamer=rhs.ostreamer;return*this;}
    ostreamable_any&operator=(ostreamable_any&rhs){data=rhs.data;ostreamer=rhs.ostreamer;return*this;}
    ostreamable_any&operator=(ostreamable_any&&rhs){data=std::move(rhs.data);ostreamer=std::move(rhs.ostreamer);return*this;}
    template<class T>ostreamable_any&operator=(T&&rhs){data=rhs;ostreamer=[](std::ostream&o,const boost::any&v)->std::ostream&{return o<<boost::any_cast<T>(v);};return*this;}
    friend std::ostream& operator<<(std::ostream&o,const ostreamable_any&rhs){return rhs.ostreamer(o,rhs.data);}
private:
    boost::any data;
    std::function<std::ostream&(std::ostream&,const boost::any&)> ostreamer;
};

int main(){
    ostreamable_any a = 5;
    std::cout << a << '\n';
}