#include <iostream>
#include <list>
#include <thread>

void thread_func()
{
    std::cout << "Hello\n";
}

int main() {
	std::list<std::thread> threads;
    std::list<std::thread> finished;
	
	for (unsigned i = 0; i < 10; ++i)
	{
		threads.emplace_back([i](){std::cout << "Thread " << i << "\n";});
	}
	
    for (auto& t : threads)
    {
        finished.emplace_back(std::move(t));
    }
    
	for (auto& t : finished)
	{
		t.join();
	}

	return 0;
}