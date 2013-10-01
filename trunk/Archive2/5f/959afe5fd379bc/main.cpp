#include <utility>
#include <iostream>

class NotDerivedAnymore {
    double A;

public:
    NotDerivedAnymore(double a) : A(a) {}
    double fn(double x) { return A*x;}
};

//Some other implementations

template <class Impl>
class algo {
    double T;
    Impl impl;

public:
    algo(double t, Impl&& impl)
        : T{t}, impl{std::forward<Impl>(impl)}
    { }

    double method(double x){ return T * impl.fn(x); }

};

template <class Impl>
algo<Impl> make_algo(double t, Impl&& impl)
{
    return algo<Impl>{t, std::forward<Impl>(impl)};
}

int main(){
    auto a = make_algo(3.2, NotDerivedAnymore{123.2});
    std::cout << a.method(2.4) << std::endl;

    return 0;
}
