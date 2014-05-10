#include <iostream>


template<typename T>
struct doto_t
{
    doto_t(T& t) : t(t) {}    
    T& t;
};


template<typename T, typename F>
doto_t<T>&& operator<<(doto_t<T>&& doto, F&& f)
{
    f(doto.t);
    return std::forward<doto_t<T>>(doto);
}


template<typename T>
std::ostream& operator<<(std::ostream& os, const doto_t<T>& doto)
{
    return os << doto.t;
}


template<typename T>
inline doto_t<T> doto(T& t)
{
    return doto_t<T>(t);
}


int main()
{
    auto inc = [](int& x) { 
        x++;
        std::cout << x << std::endl; // debug
    };


    int n = 0;
    doto(n) << inc << inc << inc;
}
