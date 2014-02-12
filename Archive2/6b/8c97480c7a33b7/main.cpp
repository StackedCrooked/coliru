#include <iostream>
#include <atomic>
#include <thread>

int x = 0;
std::atomic<int> y(x);

void f()
{
    while(++x < 100)
		std::cout << std::this_thread::get_id() << ": " << x << std::endl;
}

int main()
{
	std::thread t(f);
	std::thread t1(f);

	t.join();
	t1.join();

	return 0;
}
