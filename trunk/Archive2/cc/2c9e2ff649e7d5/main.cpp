#include <memory>
#include <chrono>
#include <iostream>

int main()
{
    const int num_iterations = 10000000;

    // Raw pointer.
	auto raw_start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < num_iterations; ++i)
	{
		auto x = new int{ 5 };
		delete x;
	}
	auto raw_end = std::chrono::high_resolution_clock::now();

	// unique_ptr
	auto unique_start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < num_iterations; ++i)
	{
		auto x = std::unique_ptr<int>{ new int { 5 } };
	}
	auto unique_end = std::chrono::high_resolution_clock::now();

	// shared_ptr using make_shared
	auto make_shared_start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < num_iterations; ++i)
	{
		auto x = std::make_shared<int>(5);
	}
	auto make_shared_end = std::chrono::high_resolution_clock::now();

	// shared_ptr constructor
	auto shared_ctor_start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < num_iterations; ++i)
	{
		auto x = std::shared_ptr<int>{ new int{ 5 } };
	}
	auto shared_ctor_end = std::chrono::high_resolution_clock::now();

	std::cout << "Raw pointer: " << std::chrono::duration_cast<std::chrono::milliseconds>(raw_end - raw_start).count() << "ms" << std::endl;
	std::cout << "unique_ptr: " << std::chrono::duration_cast<std::chrono::milliseconds>(unique_end - unique_start).count() << "ms" << std::endl;
	std::cout << "make_shared: " << std::chrono::duration_cast<std::chrono::milliseconds>(make_shared_end - make_shared_start).count() << "ms" << std::endl;
	std::cout << "shared_ptr c'tor: " << std::chrono::duration_cast<std::chrono::milliseconds>(shared_ctor_end - shared_ctor_start).count() << "ms" << std::endl;
}
