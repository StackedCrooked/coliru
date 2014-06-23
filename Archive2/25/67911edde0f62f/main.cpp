#include <map>
#include <iostream>

int main () {
    std::map<int,int> test;
    test[5] = 7;
    
    std::cout << test.begin()->first;
}
    