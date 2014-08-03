#include <iostream>
#include <chrono>
#include <thread>

void other_thread() {
    std::chrono::milliseconds dura( 2000 );
    std::this_thread::sleep_for( dura );
    std::cout << "Waited 2000 ms\n";
}

int main()
{
    std::thread t(other_thread);
    std::cout << "Waiting 2 seconds in a secondary thread.." << std::endl;
    t.join();
	std::cout << "Thread has completed its job" << std::endl;
	return 0;
}