#include <functional>

template<class F>
struct fixed{
    F f;
    template<class... Args>
    auto operator()(Args... args){
        return f(*this, args...);
    }
};

template<class F>
fixed<F> fix(F f){
    return {f};
}

#include <utility>


#include <iostream>

struct fac_t{
    template<class F>
    int operator()(F f, int i){
        return i == 0? 1 : i * f(i-1);
    }
};

fac_t fac{};

int main(){
    auto lfac = fix(fac);
    std::cout << lfac(5);
}
