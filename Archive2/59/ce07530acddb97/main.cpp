#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

ostream& operator<<(ostream& self, std::vector<int> v);

#define sort(cmp, array) sort(begin(array), end(array), [](auto a, auto b) { return cmp; })

int main() {
    vector<int> v = {4, 1, 2, 5, 3};
	
	cout << v;
	sort(a < b, v);
	cout << v;
	
	return 0;
}

// BOILERPLATE
ostream& operator<<(ostream& self, std::vector<int> v)
{
	for (int x : v) {
		self << x << ' ';
	}
	self << endl;
	return self;
}
// ENDBOILERPLATE