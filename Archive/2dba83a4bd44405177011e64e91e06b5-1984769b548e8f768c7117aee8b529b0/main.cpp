#include <iostream>

using namespace std;

int x;

struct iy
{
    iy() {
        cout << "iy()" << endl;
		x = 6;
	}

	iy(int i) {
        cout << "iy(" << i << ")" << endl;
		x = i;
	}
};

class l
{
public:
	l(int i) : x(i) {}

	void load() {
		iy(x);
	}
private:
	int x;
};

int main()
{
	l l(42);
	l.load();
	std::cout << x << std::endl;
}
