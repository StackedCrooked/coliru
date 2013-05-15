#include <utility>
#include <type_traits>

template<class L, class R>
struct composed_t{
    L l; R r;
    
    template<class... Ts>
    auto operator()(Ts&&... vs) -> decltype(r(l(std::forward<Ts>(vs)...)))
    { return r(l(std::forward<Ts>(vs)...)); }
};

template<class L>
struct composer{
    L l;
    
    template<class R>
    composer<composed_t<L, R>> then(R r) const{ return {{l, r}}; }
    
    template<class... Ts>
    auto operator()(Ts&&... vs) -> decltype(l(std::forward<Ts>(vs)...))
    { return l(std::forward<Ts>(vs)...); }
};

template<class F>
composer<F> lift(F f){ return {f}; }

struct chainer{
    template<class F>
    composer<F> chain(F f){ return {f}; }
    
    template<class F, class... Fs>
    auto chain(F f, Fs... fs) -> decltype(lift(f).then(chain(fs...)))
    { return lift(f).then(chain(fs...)); }
};

template<class... Fs>
auto chain(Fs... fs) -> decltype(chainer().chain(fs...))
{ return chainer().chain(fs...); }

#include <iostream>

int f(int i){ return i * 2; }
int g(int i){ return i + 4; }
int h(int i){ return i - 10; }
void x(int i){ std::cout << "At first there was " << i << '\n'; }
void y( ) { std::cout << "And then there was nothing" << '\n'; };

int main(){
    auto comp1 = lift([](int item){ return item + 100; }).then(f).then(g).then(h);
    auto comp2 = chain([](int item){ return item + 100; }, f, g, h);
    auto comp3 = chain( x, y );
    std::cout << comp1(3) << "\n" << comp2(3);
    comp3( 3 );
}