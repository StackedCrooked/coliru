#include <functional>

#define SC(A) static_cast<char>(lfac(5)-(A))

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
//lfac(5)
int main(){
    auto lfac = fix(fac);
    std::cout << SC(18) << SC(12) << SC(9) << SC(6) << SC(15) << SC(5);
}
