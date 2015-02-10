#include <iostream>

class Object {};

void take(Object &) {}

int main() {
    take(Object());

	return 0;
}