#include <iostream>

template <class deleter_t> class id {
    public:
		id(deleter_t deleter) : d(deleter) {
		};
        // I want it to use whichever ~id() compiles
		~id() {
			d();
		}
		~id() {
			d(1);
		}
	private:
		deleter_t d;
};

void deleter_one() {
	std::cout << "Delete without size was called!\n";
}

void deleter_two(int size) {
	std::cout << "Delete with size=" << size << "was called!\n";
}

int main() {
	auto one = id(deleter_one);
	auto two = id(deleter_two);
}