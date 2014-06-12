#include <iostream>
#include <vector>

template<typename IT>
void bubble_sort(IT begin, IT end) {
    while (true) {
        bool swapped = false;
        for (IT i = begin; i != end-1; i = i+1) {
            if (*i > *(i+1)) {
                std::iter_swap(i, i+1);
                swapped = true;
            }
        }
        if (swapped == false) return;
    }
}

int main() {
    std::vector<int> v = {1, 6, 2, 75, 3, 233};
    bubble_sort(v.begin(), v.end());
    for (auto i : v) std::cout << i << ' ';
}