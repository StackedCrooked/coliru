#include <functional>
#include <future>
#include <iostream>
#include <chrono>
#include <stdexcept>
#include <thread>

using namespace std::literals::chrono_literals;

int slowsum(int v1, int v2)
{
    std::cout << "I take too much time for a simple add operation..." << std::endl;
	std::this_thread::sleep_for(3s);
	
	throw std::invalid_argument("lol");

	return v1 + v2;
}

int main(void)
{
	std::cout << "main begins" << std::endl;

	auto future = std::async(std::launch::async, std::bind(slowsum, 5, 5));

	std::this_thread::sleep_for(3s);

	try {
		std::cout << "compute: " << future.get() << std::endl;
	} catch (const std::exception &ex) {
		std::cout << ex.what() << std::endl;
	}

	return 0;
}