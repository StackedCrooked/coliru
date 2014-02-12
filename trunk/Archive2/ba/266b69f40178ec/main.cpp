#include <iostream>

class C {
public:
    int getStaticVar() {
		return statvar;
	}
	void setStaticVar(int x) {
		statvar = x;
	}
	static int statvar; // the static variable
};

int C::statvar = 0; // the initialization

int main() {
	C c;
	c.setStaticVar(8);
	std::cout << "C: " << c.getStaticVar() << std::endl;
	return 0;
}