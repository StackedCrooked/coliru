#include <thread>
#include <mutex>
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>


/// synchronize console output
std::mutex print_mutex;

void print()
{
    std::cout << std::endl;
}

template<typename T,typename... Args>
void print(T t,Args... args)
{
    std::cout << t;
	if (sizeof...(args))
		print(args...);
	else {
		std::cout << std::endl;
	}
}

template<typename T,typename... Args>
void sync_print(T t,Args... args)
{
	//std::unique_lock<std::mutex> lock(print_mutex);
	print(t,args...);
}

int main() {
	std::vector<std::thread> threads;
	for (int i=0; i<50; i++)
		threads.push_back(std::thread(
			[=]{ sync_print("thread: ",i); }
		));
		
	for (auto& t : threads)
		t.join();
}
