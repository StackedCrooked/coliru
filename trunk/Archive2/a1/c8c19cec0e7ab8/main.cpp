#include <iostream>

class CClass {
public:
    CClass(void *) {
		std::cout << "ctor" << std::endl;
	}
	void Foo(void) const {
		std::cout << "foo" << std::endl;
	}
};

void TestFunc(const CClass &obj = nullptr) {
	obj.Foo();
}

int main(int, char *[]) {
    std::cout << "g++ version - " << __GNUC__ << '.' << __GNUC_MINOR__ << '.' << __GNUC_PATCHLEVEL__ << std::endl;
	TestFunc();
	return 0;
}
