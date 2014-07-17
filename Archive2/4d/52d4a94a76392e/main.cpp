#include <iostream>
#include <thread>
#include <functional>
#include <unistd.h>

class parallel {
public:
    parallel() : value(0) {}
    ~parallel() {}
	int value;
	void increment() {
		for (int i=0;i<5;++i) {
			value += i;
			std::cout << value << ' ';
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}
};

int main() {
	parallel test;
	std::thread t(&parallel::increment, std::ref(test));
	
	for (int i=0;i<5;++i) {
        sleep(2);
		std::cout << test.value << '\n';
	}

	t.join();
	return 0;
}