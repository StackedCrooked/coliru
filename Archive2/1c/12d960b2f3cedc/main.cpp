#include <iostream>
#include <string>

template <int N>
class tri {
    std::string s;
public:
	tri() { s = tri<N - 1>().to_string() + "\n*" + std::string(N - 1, ' ') + "*"; }
	std::string to_string() { return s; }
};

template <>
class tri < 1 > {
public:
	std::string to_string() { return "*\n**"; }
};

int main(){
	static const int N = 7;
	std::cout << tri<N - 2>().to_string() + "\n" + std::string(N, '*');
}
