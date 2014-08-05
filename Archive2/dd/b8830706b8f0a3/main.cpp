#include <algorithm>
#include <valarray>
#include <functional>
#include <iostream>

//generates a list of [from,to] in increments of step. last is <= to with precision of step
template<typename T> std::valarray<T> range(T from, T to, T step = 1) {
    size_t elems = (size_t)floor((to-from)/step) + 1;
    std::valarray<T> result(elems);
    for (int i = 0; i < elems; i++) {
        result[i] = from+step*i;
    }
    return result;
}

//map over multiple lists as arguments to the provided function
template<typename F, typename T, typename... Ts> void mapthreadv(F func, std::valarray<T> &in, std::valarray<Ts>&... rest) {
    for (int i = 0; i < in.size(); i++) {
        func(in[i],rest[i]...);
    }
}

int main(int argc, char **argv) {  
    auto first = range(0.0,1.0,0.1);
    auto second = range(0.0,10.0,1.0);
    auto third = range(0.0,100.0,10.0);
    mapthreadv([](double a, double b, double c) { std::cout << '{' << a << ',' << b << ',' << c << "},"; },first,second,third);
}   