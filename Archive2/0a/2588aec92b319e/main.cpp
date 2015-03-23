#include <future>
#include <iostream>
#include <thread>

int main() {
    std::packaged_task<void ()> task([] { std::cout << "Hello World!" << std::endl; });
	task.get_future();
	
	try {
		task();
	}
    catch (const std::system_error& e) {
		std::cerr << "system_error: " << e.code() << std::endl;
	}
	catch (const std::future_error& e) {
		std::cerr << "future_error: " <<e.code() << std::endl;
	}
}
