#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <tr1/random>

template <template <typename...> class templateClass, typename... Ts>
//templateClass<Ts...> make(Ts... ts) {
auto make(Ts... ts) -> decltype(templateClass<Ts...>{ts...}) {
    return templateClass<Ts...>{ts...};
}

template <typename T>
struct twisterize {
    const T min;
    const T max;
    twisterize(const T & min, const T & max) : min(min), max(max) {}
    void operator()(T & x) {
        typedef std::tr1::mt19937 rng_t;
        typedef std::tr1::uniform_real<T> dist_t;
        
        static rng_t rng( ((std::tr1::random_device())) ());//most vexing parse, yikes
    	static dist_t dist(min, max);// [-0.5,0.5)
        static std::tr1::variate_generator<rng_t, dist_t> bound_dist(rng, dist);//it seems you need this in tr1 to get the expected result
        
        x = bound_dist();
        
        auto test = make<std::tr1::variate_generator>(rng, dist);
        x = test();
    }
};

template <typename T>
std::ostream & operator<<(std::ostream & out, std::vector<T> vec) {
	out << '{';
	for (size_t i = 0; i < vec.size() - 1; ++i) {
		out << vec[i] << ", ";
	}
	if (vec.size() > 0) {
		out << vec.back();
	}
	out << '}';
	return out;
}

int main() {
	std::vector<double> myVector(10);
	std::for_each(myVector.begin(), myVector.end(), twisterize<double>(-0.5, 0.5));
	std::cout << myVector << std::endl;
}
