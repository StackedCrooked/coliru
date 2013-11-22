#include <iostream>

template<typename T>
void print(T t) {
	std::cout << t;
}

template<typename T, typename... Ts>
void print(T t, Ts&&... ts) {
	print(t);
	print(ts...);
}

struct oink{};

int main() {
    print(oink());
}