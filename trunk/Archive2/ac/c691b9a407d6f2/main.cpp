#include <iostream>
#include <utility>

template <typename... Funcs>
struct composer;

template <>
struct composer<> {
    auto operator()() {
		return [&] (auto v) { return v; };
	}
};

template <typename Func, typename... Funcs>
struct composer<Func, Funcs...> {
	auto operator()(Func&& f, Funcs&&... fs) {
		composer<Funcs...> c;
		return [&] (auto v) {
			return f(c(std::forward<Funcs>(fs)...)(v));
		};
	}
};

template <typename... Funcs>
auto compose(Funcs&&... fs) {
	composer<Funcs...> c;
	return c(std::forward<Funcs>(fs)...);
}


int main (int argc, char const* argv[]) {
	float v = 3.5f;
	auto t = compose([] (auto v) { return v >= 3; }, [] (auto v) { return int(v-0.5); })(v);
	std::cout << std::boolalpha << t << "\n";
	auto f = compose([] (auto v) { return v > 3; }, [] (auto v) { return int(v-0.5); })(v);
	std::cout << std::boolalpha << f << "\n";
}