//compiled with: »g++ UZ02_Pfeiler_Stepanov.cpp -std=c++11 -o nulladdition«
#include <iostream>

template<typename T>
inline T get_limit() {
    constexpr T a {1};
	T x {1};
	while((a + x) != a)
		x *= 0.5;
	return x;
}

int main(int argc, char* argv[]) {
	std::string arg;
	if(argc==2) arg = {argv[1]};//read first parameter into string
	if(argc!=2 || (arg!="float" && arg!="double")) {//reversed program invariant
		std::cout << "Usage: " << argv[0] << " [float | double]" << std::endl;
		return 0;
	}
	std::cout << "limit: " << (arg=="float" ? get_limit<float>() : get_limit<double>()) << std::endl;
}