#include <iostream>

template <class deleter_t> class id {
	private:
		deleter_t d;
        
        template<typename Deleter>
        static auto call_deleter(Deleter& deleter)
        -> decltype( deleter() )
        { return deleter(); }
        
        template<typename Deleter>
        static auto call_deleter(Deleter& deleter)
        -> decltype( deleter(1) )
        { return deleter(1); }
        
	public:
		id(deleter_t deleter) : d(deleter) {
		};
		~id() {
			call_deleter(d);
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