#include <iostream>

struct Control {
    Control() {
		std::cout << "Control ctor @" << this << '\n';
	}

	virtual void test() {
		std::cout << "Control::test @" << this << '\n';
	}
};

struct Container : virtual Control {
	Container() {
		std::cout << "Container ctor @" << this << '\n';
	}

	virtual void test() override {
		std::cout << "Container::test @" << this << '\n';
	}
};

struct Button : virtual Control, private Container {
	Button() {
		std::cout << "Button ctor @" << this << '\n';
	}
};

int main() {
	Button b;
	b.test();
}