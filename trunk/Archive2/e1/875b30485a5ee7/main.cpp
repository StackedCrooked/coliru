#include <vector>
#include <iostream>

using namespace std;

template <typename I, typename V>
bool iter_valid(I&& i, V&& v)
{
    return v.begin() <= i && i <= v.end();
}

int main ()
{
	using V = std::vector<int>;
	using I = typename V::iterator;
	V a{1, 2, 3}, b{1, 2, 3};
	I i = ++a.begin();
	cout << iter_valid(i, a) << " " << iter_valid(i, b) << endl;
}
