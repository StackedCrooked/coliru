#include <iostream>
#include <boost/tuple/tuple.hpp>

template <size_t I, typename T, typename U>
struct AccessImpl;

template <size_t I, typename T, typename U>
struct AccessImpl {
    template <typename Tuple>
	static T& impl(Tuple& tuple) {
		typedef typename ::boost::tuples::element<I+1, Tuple>::type Next;
		return AccessImpl<I+1, T, Next>::impl(tuple);
	}
};

template <size_t I, typename T>
struct AccessImpl<I, T, T> {
	template <typename Tuple>
	static T& impl(Tuple& tuple) { return boost::get<I>(tuple); }
};

template <typename T, typename Tuple>
T& access(Tuple& tuple) {
    typedef typename ::boost::tuples::element<0, Tuple>::type Head;
	return AccessImpl<0, T, Head>::impl(tuple);
}

int main() {
	boost::tuples::tuple<char, int, std::string> example('a', 1, "Hello, World!");
	std::cout << access<std::string>(example) << "\n";
	return 0;
}
