#include <iostream>
using namespace std;

auto foo() {
    return 1234567890123456789LL;
}

int main() {
	auto f = foo();
	cout << sizeof(f) << endl;
	return 0;
}
