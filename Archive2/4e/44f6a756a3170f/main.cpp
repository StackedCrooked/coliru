#include <boost/optional.hpp>

template<class T> T optional_unwrap(T&& t) {return std::forward<T>(t);}
template<class T> T& optional_unwrap(boost::optional<T>& t) {return *t;}
template<class T> T&& optional_unwrap(boost::optional<T>&& t) {return std::move(*t);}
template<class T> const T& optional_unwrap(const boost::optional<T>& t) {return *t;}

template<class T> bool optional_has_data(T&& t) {return true;}
template<class T> bool optional_has_data(boost::optional<T>& t) {return !!t;}
template<class T> bool optional_has_data(boost::optional<T>&& t) {return !!t;}
template<class T> bool optional_has_data(const boost::optional<T>& t) {return !!t;}

bool all_true() {return true;}
template<class...Ps> bool all_true(bool first, Ps...Vs) {return first && all_true(Vs...);}

template<class func_type, class...Ps> 
auto optionalfunc(func_type func, Ps...Vs) 
-> boost::optional<decltype(func(optional_unwrap(std::forward<Ps>(Vs))...))>
{
    boost::optional<decltype(func(optional_unwrap(std::forward<Ps>(Vs))...))> ret;
    if (all_true(optional_has_data(Vs)...))
        ret = func(optional_unwrap(std::forward<Ps>(Vs))...);
    return ret;
}




#include <iostream>
#include <string>

int main() {
    boost::optional<double> a = 3.0;
    boost::optional<int> b;
    char c = 3;
    boost::optional<double> d = optionalfunc(std::divides<double>(), a, b);
    if (d) std::cout << *d;
    else std::cout << "NULL";
    std::cout << "\n";
    boost::optional<double> e = optionalfunc(std::divides<double>(), a, c);
    if (e) std::cout << *e;
    else std::cout << "NULL";
    std::cout << "\n";
    
}