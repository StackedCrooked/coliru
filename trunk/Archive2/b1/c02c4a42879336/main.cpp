#include <vector>

class A
{
public:
    int &x;
	A(int &_x): x(_x) {}
};

int main()
{
	std::vector<A> v;
	int x = 0;
	v.push_back(A(x));
}
