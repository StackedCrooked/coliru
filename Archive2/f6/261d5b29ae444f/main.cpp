#include <algorithm>
#include <iostream>
#include <functional>
#include <string>
#include <vector>

template<class Iter>
void PrintVec(Iter begin, Iter end) {
    while (begin != end) {
        // We know that *begin returns an int here, but it is not clear from the API.
        std::cout << "  *" << *begin++ << "\n";
    }
}

template <class T>
void PrintVec2(const std::vector<T>& vec) {
    // Here T can be T or reference_wrapper<T>.
    for (T e : vec) {
        // T is either int or reference_wrapper<int> but it is not clear from the API.
        std::cout << "  *" << e;
    }
    std::cout << "\n";
}

int main()
{
    std::vector<int> backing_store = {1, 4, 9, 2, 3, 22, 20};
    std::vector<std::reference_wrapper<int>> wrapper(backing_store.begin(), backing_store.end());
    
    std::sort(wrapper.begin(), wrapper.end());
    std::cout << "Backing store: \n";
    PrintVec(backing_store.begin(), backing_store.end());
    
    std::cout << "Wrapper: \n";
    PrintVec(wrapper.begin(), wrapper.end());
    
    std::cout << "Different API\n";
    PrintVec2(backing_store);
    PrintVec2(wrapper);
}
