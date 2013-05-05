#include <iostream>

void non_sized();
void sized(int);

template <typename d_t> void call_d(d_t d);
template <>
void call_d(decltype(non_sized) d) {
    d();
}
template <>
void call_d(decltype(sized) d) {
	d(1);
}


template <class deleter_t> class id {
	private:
		deleter_t d;
	public:
		id(deleter_t deleter) : d(deleter) {
		};
		~id() {
			call_d(d);
		}
};

void deleter_one() {
	std::cout << "Delete without size was called!\n";
}

void deleter_two(int size) {
	std::cout << "Delete with size=" << size << "was called!\n";
}

int main() {
	auto one = id<decltype(&deleter_one)>(deleter_one);
	auto two = id<decltype(&deleter_two)>(deleter_two);
}