#include <vector>
#include <iostream>
#include <algorithm>


int main() {
    std::vector<int> A{1, 2, 3, 2, 4, 6, 5};
    std::vector<int> search_range{2, 4, 6};
    std::vector<int> find_first_of_range{6, 5};

    auto it_search = std::search(A.begin(), A.end(),
        search_range.begin(), search_range.end());
    std::cout << std::distance(A.begin(), it_search) << std::endl; // 3

    auto it_find_first_of = std::find_first_of(A.begin(), A.end(),
        find_first_of_range.begin(), find_first_of_range.end());
    std::cout << std::distance(A.begin(), it_find_first_of) << std::endl; // 5
}