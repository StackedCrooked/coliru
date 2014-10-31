#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <utility>

using namespace std;

template<typename T, typename Func>
std::vector<typename std::result_of<Func(T)>::type>
  map1(const std::vector<T> &v, Func f) {
    std::vector<typename std::result_of<Func(T)>::type> res;
    res.reserve(v.size());
    std::transform(std::begin(v), std::end(v), std::inserter(res, res.begin()), f);
    return res;
}

template<typename T, typename Func>
std::vector<decltype(std::declval<Func>()(std::declval<T>()))>
  map2(const std::vector<T> &v, Func f) {
    std::vector<decltype(std::declval<Func>()(std::declval<T>()))> res;
    res.reserve(v.size());
    std::transform(std::begin(v), std::end(v), std::inserter(res, res.begin()), f);
    return res;
}

template<typename T, typename Func>
auto map3(const std::vector<T> &v, Func f) 
  -> std::vector<decltype(f(v[0]))> {
    std::vector<decltype(f(v[0]))> res;
    res.reserve(v.size());
    std::transform(std::begin(v), std::end(v), std::inserter(res, res.begin()), f);
    return res;
}

int main() {
    vector<int> numbers = { 1, 3, 5 };
	
    {
    	vector<string> strings = map1(numbers, [] (int const& x) { return string(x,'X'); });
    	
    	for (const string& s : strings) {
    		cout << s << "\n";
    	}
    }
    {
        vector<string> strings = map2(numbers, [] (int const& x) { return string(x,'X'); });
    	
    	for (const string& s : strings) {
    		cout << s << "\n";
    	}
    }
    {
        vector<string> strings = map3(numbers, [] (int const& x) { return string(x,'X'); });
        
    	for (const string& s : strings) {
    		cout << s << "\n";
    	}
    }
	
	return 0;
}
