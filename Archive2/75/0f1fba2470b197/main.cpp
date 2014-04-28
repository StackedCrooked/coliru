#include <iostream>
#include <iterator>

template<typename It, typename Elem>
bool in_ranges(It first, It last, It first2, Elem val) {
    for (; first != last; ++first, ++first2) {
        if (*first <= val && val <= *first2) {
            return true;
        }
    }
    
    return false;
}

int main() {
    int starts[] = {11, 31, 51, 71, 91};
    int ends[] = {20, 40, 60, 80, 100};
    
    const int num = 15;
    
    std::cout << in_ranges(std::begin(starts), std::end(starts), std::begin(ends), num);
}