#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <vector>

thread_local std::vector<int> rage = 1;
std::mutex cout_mutex;

void increase_rage(const std::string& thread_name)
{
    rage.push_back(1);
	std::lock_guard<std::mutex> lock(cout_mutex);
	std::cout << "Rage counter for " << thread_name << ": " ;
    for(auto i:rage) cout<< i << '\n';
}

int main()
{
	std::thread a(increase_rage, "a"), b(increase_rage, "b");

	{
		std::lock_guard<std::mutex> lock(cout_mutex);
		std::cout << "Rage counter for main: " ;
         for(auto i:rage) cout<< i << '\n';
	}

	a.join();
	b.join();

	return 0;
}