#include <iostream>
#include <vector>

struct Test {
    std::vector<int> data;
    decltype(data.begin()) begin() {
        return data.begin();    
    }
};

int main() {    
    Test test;
    test.begin();
    return 0;
}