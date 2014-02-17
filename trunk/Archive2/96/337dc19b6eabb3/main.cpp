#include <iostream>
#include <string>
#include <vector>

#include <boost/variant.hpp>
#include <boost/function_types/function_type.hpp>

typedef boost::variant<int, double> Type;

struct Functor : std::function<int(int, double)> {
    int operator ()(int i, double d) const {
        return i;   
    }
};

template<typename From, int N, typename To>
struct Convert;

template<typename From, int N>
struct Convert<From, N, int> {
    int operator ()(From f) const {
        return boost::get<int>(f[N]);
    }
};

template<typename From, int N>
struct Convert<From, N, double> {
    int operator ()(From f) const {
        return boost::get<double>(f[N]);   
    }
};

template<typename Args, int N, typename Sig>
struct UnfoldArguments;

template<typename Args, int N, typename R, typename Arg, typename...FArgs>
struct UnfoldArguments<Args, N, std::function<R(Arg, FArgs...)>> {
    
    UnfoldArguments(Args& args) : arg(convert(args)), unfoldArguments(args) {
    }
    
    template<typename...A, typename...B>    
    R operator ()(std::function<R(A...)> functor, B...args) {
        return unfoldArguments(functor, arg, args...);
    }
    
    Convert<Args, N, Arg> convert;
    Arg arg;
    UnfoldArguments<Args, N+1, std::function<R(FArgs...)>> unfoldArguments;
};

template<typename Args, int N, typename R, typename Arg>
struct UnfoldArguments<Args, N, std::function<R(Arg)>> {
    
    UnfoldArguments(Args& args) : arg(convert(args)) {
    }
    
    template<typename...A, typename ...B>
    R operator ()(std::function<R(A...)> functor, B...args) {
        return functor(arg, args...);
    }
    
    Convert<Args, N, Arg> convert;
    Arg arg;
};

typedef std::vector<Type> TypeSeq;

template<typename R, typename...FArgs>
void mainfun(std::function<R(FArgs...)> functor) {
    TypeSeq seq;
    seq.push_back(3);
    seq.push_back(.4);
    
    std::cout <<
    UnfoldArguments<TypeSeq, 0, std::function<R(FArgs...)>>(seq)(functor)
    << std::endl;
}


int main() {
    Functor f;
    mainfun(f);
    return 0;
}