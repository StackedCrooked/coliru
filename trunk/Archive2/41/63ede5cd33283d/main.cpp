#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

using namespace std;

template<typename T>
struct identity
{
    using type = T;
};
template<typename T>
using identity_t = typename identity<T>::type;

template<typename T>
std::vector<T> map(const std::vector<T> &v, identity_t<std::function<T(T)>> f) {
    std::vector<T> result;
    result.push_back(f(v[0]));
    return result;
}


int main() {
    vector<int> numbers = { 1, 3, 5 };
    
	std::cout << map(numbers, [](int i){ return i * 10; })[0] << endl;
}
