#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <utility>

using namespace std;

template<typename T, typename Func>
std::vector<typename std::result_of<Func(T)>::type>
  map(const std::vector<T> &v, Func f) {
    std::vector<typename std::result_of<Func(T)>::type> res;
    res.reserve(v.size());
    std::transform(std::begin(v), std::end(v), std::inserter(res, res.begin()), f);
    return res;
}


int main() {
    vector<int> numbers = { 1, 3, 5 };
	
	vector<string> strings = map(numbers, [] (int const& x) { return string(x,'X'); });
	
	for (const string& s : strings) {
		cout << s << "\n";
	}
	
	return 0;
}
