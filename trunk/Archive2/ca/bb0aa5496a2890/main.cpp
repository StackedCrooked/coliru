#include <array>
#include <atomic>
#include <iostream>
#include <mutex>
#include <thread>

std::atomic_int readsPermitted;
std::atomic_int writePermitted;
std::mutex outputMutex;

const size_t size = 5;
std::array<size_t, size> buffer;

void consumer() {
    std::cout << "\tconsumer start" << std::endl;
	for (size_t productNr = 0; productNr != 20; ++productNr) {

		while(!readsPermitted);
        --readsPermitted;

		auto index = productNr % size;
		auto value = buffer[index];

		++writePermitted;

		std::lock_guard<std::mutex> lock(outputMutex);
		std::cout << "\tconsumer, index " << index << ", read " << value << std::endl;
	}
}

void producer() {
	std::cout << "producer start" << std::endl;
	for (size_t productNr = 0; productNr != 20; ++productNr) {

		while(!writePermitted);
        --writePermitted;

		size_t index = productNr % size;
		buffer[index] = productNr;

		++readsPermitted;

		std::lock_guard<std::mutex> lock(outputMutex);
		std::cout << "producer, index " << index << ", wrote " << productNr << std::endl;
	}
}

int main() {
	readsPermitted = 0;
	writePermitted = size;

	std::thread t1(producer);
	std::thread t2(consumer);

    if (t1.joinable()) t1.join();
    if (t2.joinable()) t2.join();
}
