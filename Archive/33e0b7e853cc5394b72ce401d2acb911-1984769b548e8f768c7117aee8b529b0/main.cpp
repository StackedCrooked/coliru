#include <iostream>

using namespace std;

int x;

struct i
{
    i() {
        cout << "i()" << endl;
		x = 0;
	}

	i(int i) {
        cout << "i(" << i << ")" << endl;
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
