#include <iostream>
#include <numeric>
#include <memory>
#include <vector>

using namespace std;

template <typename T>
std::unique_ptr<T> empty() {
	return std::unique_ptr<T>(nullptr);
}

template <typename T>
std::unique_ptr<T> alternative(const std::unique_ptr<T>& p1, const std::unique_ptr<T>& p2) 
{
	if (p1) return std::unique_ptr<T>(new T(*p1));
	if (p2) return std::unique_ptr<T>(new T(*p2));
	return empty<T>();
}

int main()
{
    vector<unique_ptr<int>> vec;
    vec.emplace_back(new int(1));
    vec.emplace_back(new int(2));
    auto acc = std::accumulate(begin(vec), end(vec), 
        empty<int>(), alternative<int>);
    cout << *acc << endl;
}
