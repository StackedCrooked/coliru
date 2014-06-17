//Aufgabenblatt 8, »Objektorientiertes Programmieren im Wissenschaftlichen Rechnen«
//Norbert Pfeiler, Michael Pronkin & Alexander Stepanov

//exercise01
template <typename T>
struct function {
    virtual T operator()(const T &) const = 0;
};
template <typename T>
struct test_function : public function<T> {
	virtual void integrationInterval(double & l, double & r) const = 0;
	virtual double exactIntegral() const = 0;
};
template <typename T>
struct quadrature {
	virtual T operator()(const function<T> &, const T & min, const T & max) const = 0;
};

#include <cstddef>
template <typename T>
T integral(const function<T> & f, const T & min, const T & max, const std::size_t & interval_count, const quadrature<T> & q) {
	T res = 0;
	const T interval = (max - min) / interval_count;
	for (T i = min; i + interval <= max; i += interval) {
		res += q(f, i, i + interval);
	}
	return res;
}

template <template<typename> class Func, typename T>
T integral_static_dynamic(const Func<T> & f, const T & min, const T & max, const std::size_t & interval_count, const quadrature<T> & q) {
	T res = 0;
	const T interval = (max - min) / interval_count;
	for (T i = min; i + interval <= max; i += interval) {
		res += q(f, i, i + interval);
	}
	return res;
}

template <typename T, template<typename> class Quadra>
T integral_dynamic_static(const function<T> & f, const T & min, const T & max, const std::size_t & interval_count, const Quadra<T> & q) {
	T res = 0;
	const T interval = (max - min) / interval_count;
	for (T i = min; i + interval <= max; i += interval) {
		res += q(f, i, i + interval);
	}
	return res;
}

template <template<typename> class Func, typename T, template<typename> class Quadra>
T integral_static_static(const Func<T> & f, const T & min, const T & max, const std::size_t & interval_count, const Quadra<T> & q) {
	T res = 0;
	const T interval = (max - min) / interval_count;
	for (T i = min; i + interval <= max; i += interval) {
		res += q(f, i, i + interval);
	}
	return res;
}

template <typename T = double>
struct trapez : quadrature<T> {
	virtual T operator()(const function<T> & f, const T & min, const T & max) const override final {
		return (max-min)/T{2} * (f(min) + f(max));
	}
};
template <typename T = double>
struct simpson : quadrature<T> {
	virtual T operator()(const function<T> & f, const T & min, const T & max) const override final {
		return (max-min)/T{6} * (f(min) + T{4}*f((max+min)/T{2}) + f(max));
	}
};
template <typename T = double>
struct trapez_static {
    template <template<typename> class Func>
    T operator()(const Func<T> & f, const T & min, const T & max) const {
		return (max-min)/T{2} * (f(min) + f(max));
	}
};
template <typename T = double>
struct simpson_static {
    template <template<typename> class Func>
	T operator()(const Func<T> & f, const T & min, const T & max) const {
		return (max-min)/T{6} * (f(min) + T{4}*f((max+min)/T{2}) + f(max));
	}
};

template <typename T = double>
struct f1 : function<T> {
	virtual T operator()(const T & t) const override final {
		return 2 * t*t + 5;
	}
};
template <typename T = double>
struct f1_static {
    T operator()(const T & t) const {
		return 2 * t*t + 5;
	}
};

#include <chrono>
#include <iostream>
#include <vector>

template <typename T, typename Func>
double mesaure(T & results, const Func f) {
	const auto start = std::chrono::high_resolution_clock::now();
	auto res = f();
	const auto end = std::chrono::high_resolution_clock::now();
    results.emplace_back(res);
	const auto ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() / 1000.0;
	return ms;
}

int main() {
	std::vector<double> results;
    std::cout << "func   qf" << std::endl;
    std::cout << "trapez dd: " << mesaure(results, [](){return integral(f1<>{}, -3., 13., 10002, trapez<>{});}) << " ms" << std::endl;
    std::cout << "trapez sd: " << mesaure(results, [](){return integral_dynamic_static(f1<>{}, -3., 13., 10002, trapez_static<>{});}) << " ms" << std::endl;
    std::cout << "trapez ds: " << mesaure(results, [](){return integral_static_dynamic(f1<>{}, -3., 13., 10002, trapez<>{});}) << " ms" << std::endl;
	std::cout << "trapez ss: " << mesaure(results, [](){return integral_static_static(f1_static<>{}, -3., 13., 10002, trapez_static<>{});}) << " ms" << std::endl;

	std::cout << "simpson dd: " << mesaure(results, [](){return integral(f1<>{}, -3., 13., 10002, simpson<>{});}) << " ms" << std::endl;
    std::cout << "simpson sd: " << mesaure(results, [](){return integral_dynamic_static(f1<>{}, -3., 13., 10002, simpson_static<>{});}) << " ms" << std::endl;
    std::cout << "simpson ds: " << mesaure(results, [](){return integral_static_dynamic(f1<>{}, -3., 13., 10002, simpson<>{});}) << " ms" << std::endl;
	std::cout << "simpson ss: " << mesaure(results, [](){return integral_static_static(f1_static<>{}, -3., 13., 10002, simpson_static<>{});}) << " ms" << std::endl;
}
/*
combining static function dispatch with dynamic quadrature rule dispatch is not really possible
since the interface of quadrature<T> expects a function<T>

-O0
func   qf
trapez dd: 439.573 ms
trapez sd: 445.131 ms
trapez ds: 469.876 ms
trapez ss: 439.517 ms
simpson dd: 738.562 ms
simpson sd: 700.76 ms
simpson ds: 741.99 ms
simpson ss: 672.6 ms

→ slow

-O3
func   qf
trapez dd: 51.599 ms
trapez sd: 53.679 ms
trapez ds: 52.834 ms
trapez ss: 51.655 ms
simpson dd: 93.864 ms
simpson sd: 84.95 ms
simpson ds: 89.06 ms
simpson ss: 82.36 ms

→ equally fast except complete dynamic dispatch of the simpson pipeline

-O3 and __attribute__ ((noinline))
func   qf
trapez dd: 141.752 ms
trapez sd: 55.851 ms
trapez ds: 144.049 ms
trapez ss: 53.619 ms
simpson dd: 260.492 ms
simpson sd: 202.636 ms
simpson ds: 289.31 ms
simpson ss: 78.62 ms

→ the static version is obviously the fastest
dynmic dispatch costs a considerate amount of time
if it can’t be optimized out by the compiler in the first place
*/