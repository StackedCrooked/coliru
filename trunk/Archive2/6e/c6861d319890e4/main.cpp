#include <iostream>
#include <stdexcept>


int main() {
    int var = 4;
	auto fun = [var]() mutable { var = 3; };
	fun();
	std::cout << var << std::endl;
}