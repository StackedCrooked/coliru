#include <iostream>
#include <thread>
#include <vector>

struct Base {};

struct Derived: public Base {};

//void f(Base & b) {}
void f(Base * b) {}

int main() {
    Derived d;

	std::vector<std::thread> threads;
	//threads.emplace_back(f, d);
	threads.emplace_back(f, &d);

	for (auto & thread: threads)
		thread.join();

	return 0;
}