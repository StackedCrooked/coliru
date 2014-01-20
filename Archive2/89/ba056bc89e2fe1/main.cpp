#include <iostream>

struct Foo {
    int bar(int n)
	{
		int q = 0;
		for (int i = 0; i != n; ++i)
			q += i * i;
		return q;
	}
};

int main() {
	Foo x;
	std::cout << x.bar(10);
}