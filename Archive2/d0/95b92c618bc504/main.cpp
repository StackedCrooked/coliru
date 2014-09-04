struct foo {
	foo(double, int = 0) { }
	foo(double, double = 0) { }
};

struct bar : foo {
	using foo::foo;
};

int main() { }