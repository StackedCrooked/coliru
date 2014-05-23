#include <iostream>
#include <list>
#include <thread>

void thread_func()
{
    std::cout << "Hello\n";
}

int main() {
	std::list<std::thread> threads;
	
	for (unsigned i = 0; i < 10; ++i)
	{
		threads.emplace_back(thread_func);
	}
	
	for (auto& t : threads)
	{
		t.join();
	}

	return 0;
}