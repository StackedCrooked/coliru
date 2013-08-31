#include <iostream>
#include <vector>


struct Test {
    std::vector<int> my_vector;
    
    explicit Test(std::initializer_list<int> list) : my_vector(list) {}   
};


int main() {
    Test t({1, 2, 3, 4});
    
    // Testing
    for(int i : t.my_vector) std::cout << i << std::endl;
}