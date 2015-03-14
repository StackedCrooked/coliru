#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
 
const std::chrono::seconds operator "" _s(unsigned long long s)
{
    return std::chrono::seconds(s);
}
 
const std::chrono::duration<long double> operator "" _s(long double s)
{
	return std::chrono::duration<long double>(s);
}
 
int main()
{
	std::condition_variable cond;
	std::mutex mutex;
	std::unique_lock<std::mutex> lock(mutex);
	cond.wait_for(lock, 0.5_s);
    std::cout << "Success" << std::endl;
	return 0;
}