#include <iostream>
#include <thread>
 
struct foo {
    void
	bar() {
		std::thread t(&foo::baz, this);
		t.join();
	}
 
	void
	baz() {
		std::cout << value << '\n';
	}
 
	int value;
};
 
int
main() {
	foo f{5};
	f.bar();
}
