#include <iostream>
#include <string>
#include <type_traits>

constexpr std::size_t _max(std::size_t a, std::size_t b) {
    return a > b ? a : b;
}

template <class T, class... Ts>
struct MaxSize {
	static constexpr std::size_t value = _max(sizeof (T), MaxSize<Ts...>::value);
};

template <class T>
struct MaxSize<T> {
	static constexpr std::size_t value = sizeof (T);
};

template <class T, class... Ts>
struct MaxAlign {
	static constexpr std::size_t value = _max(alignof(T), MaxAlign<Ts...>::value);
};

template <class T>
struct MaxAlign<T> {
	static constexpr std::size_t value = alignof(T);
};

struct Base {

	Base(std::string const &str) : _str(str) {
    	std::cerr << "Base constructed\n";
	}

	virtual ~Base() {
		std::cerr << "Base destructed\n";
	}

	virtual void print() {
		std::cerr << "Base with " << _str << '\n';
	}

	std::string _str;
};

struct Derived1 : Base {

	Derived1(int i) : Base("drv2"), _int(i) {
        std::cerr << "Derived1 constructed\n";
	}

	~Derived1() {
		std::cerr << "Derived1 destructed\n";
	}

	void print() override {
		std::cerr << "Derived1 with " << _int << '\n';
	}

	int _int;
};

struct Derived2 : Base {

	Derived2(double d) : Base("drv2"), _dbl(d) {
        std::cerr << "Derived2 constructed\n";
	}

	~Derived2() {
		std::cerr << "Derived2 destructed\n";
	}

	void print() override {
		std::cerr << "Derived2 with " << _dbl << '\n';
	}

	double _dbl;
};

int main(int, char**) {

	alignas(MaxAlign<Base, Derived1, Derived2>::value)
	char storage[MaxSize<Base, Derived1, Derived2>::value];
	
	Derived2* dptr = new (storage) Derived2(3.14);
    std::cerr << dptr << '\n';
    Base* bptr = dptr;
    std::cerr << bptr << '\n';

    Base* bptr2 = reinterpret_cast<Base*> (storage);
    std::cerr << bptr2 << '\n';
	Base &ref = *bptr2;
    
    std::cerr << "calling print()" << '\n';
	ref.print();
    
    std::cerr << "calling dtor()" << '\n';
	ref.~Base();

    std::cerr << "done" << '\n';
	return 0;
}