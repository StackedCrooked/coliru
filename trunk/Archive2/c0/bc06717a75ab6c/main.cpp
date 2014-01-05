#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <tr1/random>

template <template <typename...> class templateClass, typename ... Ts>
//templateClass<Ts...> make(Ts... ts) {
auto make(Ts... ts) -> decltype(templateClass<Ts...>{ts...}) {
    return templateClass<Ts...>{ts...};
}

template <typename T, typename rng_t>
struct twisterize {
    const T min;
    const T max;
    const rng_t & rng;
    twisterize(const T & min, const T & max, const rng_t & rng) : min(min), max(max), rng(rng) {}
    void operator()(T & x) {
        typedef std::tr1::uniform_real<T> dist_t;
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
    typedef std::tr1::mt19937 rng_t;
    rng_t rng( ((std::tr1::random_device())) ());//most vexing parse, yikes
	srand(time(NULL));
	//myObjs = std::vector<myClass>(20, myClass(no_of_inputs));
	std::vector<double> myVector(10);
	{
		std::for_each(myVector.begin(), myVector.end(), twisterize<double, rng_t>(-0.5, 0.5, rng));
		std::cout << myVector << std::endl;
	}
}
