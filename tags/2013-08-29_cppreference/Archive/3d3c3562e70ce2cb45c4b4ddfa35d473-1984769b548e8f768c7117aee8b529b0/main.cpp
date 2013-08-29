#include <iostream>

using namespace std;

int x;

struct i
{
    i() {
		x = 0;
	}

	i(int i) {
		x = i;
	}
};

class l
{
public:
	l(int i) : x(i) {}

	void load() {
		i(x);
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
