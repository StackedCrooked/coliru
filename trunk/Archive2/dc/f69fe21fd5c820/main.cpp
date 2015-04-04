#include <cstddef>
#include <iterator>

template<typename T, typename Category>
class any_iterator : public std::iterator<Category, T, std::ptrdiff_t, T*, T&> {
public:

private:
    
};

// example:
#include <iostream>
#include <numeric>
#include <vector>

int f(any_iterator<int, std::input_iterator_tag> begin, any_iterator<int, std::input_iterator_tag> end) {
    return std::accumulate(begin, end, 0);
}

int main() {
    std::vector<int> xs{1, 2, 3};
    std::cout << f(xs.begin(), xs.end());
    return 0;
}