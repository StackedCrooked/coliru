#include <iostream>
#include <random>

template <class Generator>
double use_rand(Generator & g){
    std::normal_distribution<double> d;
	return d(g);
}

template <class Generator>
double use_rand_static(Generator & g){
	static std::normal_distribution<double> d;
	return d(g);
}

int main(){
	std::mt19937 rnumber{5};
	std::cout << "non-static version:\n";
	std::cout << use_rand(rnumber) << "\n";
	std::cout << use_rand(rnumber) << "\n\n";

	rnumber.seed(5);
	std::cout << "static version:\n";
	std::cout << use_rand_static(rnumber) << "\n";
	std::cout << use_rand_static(rnumber) << std::endl;
	return 0;
}
