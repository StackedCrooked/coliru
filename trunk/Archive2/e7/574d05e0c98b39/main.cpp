class Foo {
public:
    int operator +(int arg) {
		return arg;
	}
};

int main(int argc, char *argv[]) {
	Foo x;
	int a = 10;
	int b = 12;

	int c = x + a;
	c = x + b;
	c = x + c;


	return 0;
}

