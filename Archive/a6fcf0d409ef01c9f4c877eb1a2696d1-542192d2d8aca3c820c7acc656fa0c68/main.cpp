#include <vector>
#include <iostream>

int main() {
    std::vector<int> v{ 1, 1, 2, 2, 3, 3 };
    int count = 0;
    for(auto it = v.begin(); it != v.end()-1; ++it) {
        if(*it == it[1]) ++count;
    }
    std::cout << count;
}