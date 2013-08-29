#include <vector>
#include <iostream>

int main() {
    std::vector<int> v{ 1, 1, 2, 2, 3, 3, 3 };
    v.pop_back();
    int count = 0;
    for(auto it = v.begin(); it != v.end(); ++it) {
        if(*it != it[1]) ++count;
    }
    std::cout << count;
}