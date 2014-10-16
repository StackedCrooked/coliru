#include <iostream>
#include <utility>
#include <vector>
#include <iterator>
#include <algorithm>

template<class T>struct type_t{using type=T;};
template<class T>using get_type=typename T::type;

template<class F>
struct deduce_out_helper {
    F f;
	deduce_out_helper(F&& f_):f(std::forward<F>(f_)){}
	template<class Z>
	operator Z()&&{ return f( type_t<Z>{} ); }
};
template<class F>
deduce_out_helper<F> deduce_out( F&& f ) { return {std::forward<F>(f)}; }


template<typename T, typename Selector>
auto select(std::vector<T> const & c, Selector&& s) {
  return deduce_out( [&]( auto out ) {
  	get_type<decltype(out)> r;
    std::transform(std::begin(c), std::end(c), std::back_inserter(r), std::forward<Selector>(s));
  	return r;
  });
}

int main() {
    std::vector<int> in = {1,2,3};
    std::vector<double> out = select(in, [](int x){return x*1.5;});
    for(double d : out)
        std::cout << d << "\n";
}