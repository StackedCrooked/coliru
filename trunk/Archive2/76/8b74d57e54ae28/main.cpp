#include <algorithm>
#include <iostream>
#include <iterator>

template<typename It, typename Elem>
bool in_any_interval(It first, It last, It first2, const Elem &val) {
    return std::any_of(first, last, [&first2, val](const Elem &e) {
        return e <= val && val <= *first2++;
    });
}

int main() {
    int starts[] = {11, 31, 51, 71, 91};
    int ends[] = {20, 40, 60, 80, 100};
    
    const int num = 15;
    
    std::cout << in_any_interval(std::begin(starts), std::end(starts), std::begin(ends), num);
}