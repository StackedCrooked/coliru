#include <iostream>
using namespace std;

struct foo;

struct bar {
    bar(foo& f);
	void buzz(foo& f);
};

struct foo {
	 friend bar::bar(foo&);

private:
	int secret;
};

bar::bar(foo& f) { 
	f.secret = 10; // hłehłehle 
}

void bar::buzz(foo& f) {
	//f.secret = 10;  nope 
}

int main() {
	foo f;
	bar b(f);
	b.buzz(f);
	return 0;
}