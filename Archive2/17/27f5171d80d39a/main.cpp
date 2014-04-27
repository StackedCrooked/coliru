#include <iostream>
#include <vector>
#include <deque>

    template<typename Container>
    void cicle(Container const& c) {
        for (auto it = std::begin(c); it != std::end(c); ++it) {
            std::cout << (*it);
        }
        std::cout << '\n';
    }
    
int main() {
    std::vector<int> vec {1, 2, 3};
    cicle(vec);
    
    std::deque<int> deq {1, 2, 3};
    cicle(deq);
    
    int arr[3] = {1, 2, 3};
    cicle(arr);
}