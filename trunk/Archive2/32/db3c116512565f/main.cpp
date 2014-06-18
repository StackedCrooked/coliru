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
struct f1 : function<T> {
	virtual T operator()(const T & t) const override final {
		return 2 * t*t + 5;
	}
};

#include <chrono>
#include <iostream>
#include <vector>

template <typename T, typename Func>
double mesaure(T & results, const Func f) {
	const auto start = std::chrono::high_resolution_clock::now();
	results.emplace_back(f());
	const auto end = std::chrono::high_resolution_clock::now();
	const auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() / 1000.0;
	return ns;
}

int main() {
	std::vector<double> results;
	std::cout << "dd: " << mesaure(results, [](){return integral(f1<>{}, -3., 13., 10002, trapez<>{});}) << " ns" << std::endl;
	std::cout << "ds: " << mesaure(results, [](){return integral_dynamic_static(f1<>{}, -3., 13., 10002, trapez<>{});}) << " ns" << std::endl;
	std::cout << "sd: " << mesaure(results, [](){return integral_static_dynamic(f1<>{}, -3., 13., 10002, trapez<>{});}) << " ns" << std::endl;
	std::cout << "ss: " << mesaure(results, [](){return integral_static_static(f1<>{}, -3., 13., 10002, trapez<>{});}) << " ns" << std::endl;

	std::cout << "dd: " << mesaure(results, [](){return integral(f1<>{}, -3., 13., 10002, simpson<>{});}) << " ns" << std::endl;
	std::cout << "ds: " << mesaure(results, [](){return integral_dynamic_static(f1<>{}, -3., 13., 10002, simpson<>{});}) << " ns" << std::endl;
	std::cout << "sd: " << mesaure(results, [](){return integral_static_dynamic(f1<>{}, -3., 13., 10002, simpson<>{});}) << " ns" << std::endl;
	std::cout << "ss: " << mesaure(results, [](){return integral_static_static(f1<>{}, -3., 13., 10002, simpson<>{});}) << " ns" << std::endl;
}
