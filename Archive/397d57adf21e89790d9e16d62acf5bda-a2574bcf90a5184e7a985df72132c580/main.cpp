#include <utility>
#include <type_traits>

template<class L, class R>
struct composed_t {
    L l; R r;

	template <typename CL, typename CR, typename TLR>
	struct composed_invoker {
		template<class... Ts>
		auto operator()(R& r, L& l, Ts&&... vs) -> decltype(r(l(std::forward<Ts>(vs)...)))
		{ return r(l(std::forward<Ts>(vs)...)); }
	};

	template <typename CL, typename CR>
	struct composed_invoker<CL, CR, void> {
		template<class... Ts>
		auto operator()(R& r, L& l, Ts&&... vs) -> decltype(r())
		{ l(std::forward<Ts>(vs)...); return r(); }
	};

	template<class... Ts>
	auto operator()(Ts&&... vs) -> decltype(composed_invoker<L, R, decltype(l(std::forward<Ts>(vs)...))>()(r, l, std::forward<Ts>(vs)...)) { 
		composed_invoker<L, R, decltype(l(std::forward<Ts>(vs)...))> inv;
		return inv( r, l, std::forward<Ts>(vs)... );
	}

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
void x(int i){ std::cout << "[x:void( int )]"; }
void y( ) { std::cout << "[y:void( void )]"; };
void z( ) { std::cout << "[z:void( void )]"; };

int main(){
	auto comp1 = lift([](int item){ return item + 100; }).then(f).then(g).then(h);
	auto comp2 = chain([](int item){ return item + 100; }, f, g, h);
	auto comp3 = chain( x );
	auto comp4 = chain( x, y );
	auto comp5 = chain( y, z );
	
    std::cout << "comp1( 10 ): " << comp1( 10 ) << "\n";
	
    std::cout << "comp2( 10 ): " << comp2( 10 ) << "\n";
	
    std::cout << "comp3( 10 ): ";
    comp3( 10 );
    std::cout << "\n";
	
    std::cout << "comp4( 10 ): ";
    comp4( 10 );
    std::cout << "\n";
	
    std::cout << "comp5(    ): ";
    comp5( );
    std::cout << "\n";
}