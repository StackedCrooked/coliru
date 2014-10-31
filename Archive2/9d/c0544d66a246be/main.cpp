#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

using namespace std;

template<typename T, typename U>
std::vector<U> map(const std::vector<T> &v, std::function<U(const T&)> f) {
    std::vector<U> res;
    res.reserve(v.size());
    std::transform(std::begin(v), std::end(v), std::inserter(res, res.begin()), f);
    return res;
}


int main() {
    vector<int> numbers = { 1, 3, 5 };
	
	std::function<string(int const&)> fn = [] (int x) { return string(x,'X'); };
	vector<string> strings = map(numbers, fn);
	
	for (const string& s : strings) {
		cout << s << "\n";
	}
	
	return 0;
}
