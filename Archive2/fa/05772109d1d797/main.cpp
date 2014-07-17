#include <iostream>
#include <thread>
#include <functional>

class parallel {
public:
    parallel() : value(0) {}
	~parallel() {}
	int value;
	void increment() {
		for (int i=0;i<10;++i) {
			value += i;
			std::cout << value << ' ';
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}
};

int main() {
	parallel test;
	std::thread t(&parallel::increment, std::ref(test));
	
	for (int i=0;i<10;++i) {
		std::cout << test.value << '\n';
        std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	t.join();
	return 0;
}