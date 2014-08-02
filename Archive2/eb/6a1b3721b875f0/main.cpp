#include <iostream>

struct Layout1 {
    int a;
	double b;
	char c;
};

struct Layout2 {
	int a;
	char b;
	double c;
};

struct Layout3 {
	double a;
	int b;
	char c;
};

int main() {
	std::cout << sizeof(Layout1) << "\n";
	std::cout << sizeof(Layout2) << "\n";
	std::cout << sizeof(Layout3) << "\n";
	return 0;
}