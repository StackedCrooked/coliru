#include <iostream>
#include <vector>
using namespace std;

struct foo{
    vector<bool> v = {true, false, true};
	
	// #1
	auto operator[](size_t x) { return v[x]; }
	auto operator[](size_t x) const { return v[x]; }
};

int main() {
	foo f;
	f[0] = false;
	for(auto&& x : f.v) cout << x << " ";
}

// #2
// auto& operator[](size_t x) { return v[x]; }
// auto& operator[](size_t x) const { return v[x]; }

// #3
// auto&& operator[](size_t x) { return v[x]; }
// auto&& operator[](size_t x) const { return v[x]; }

// #4
// decltype(auto) operator[](size_t x) { return v[x]; }
// decltype(auto) operator[](size_t x) const { return v[x]; }
