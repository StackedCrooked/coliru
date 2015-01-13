
#include <iostream>
#include <array>
#include <algorithm>
#include <functional>

int* test(int &i){return *i;}

int main() {
    int t1[6] = {3,4,5,1,2,8};
    
    std::vector<int*> t2;
    
    std::transform(std::begin(t1),std::end(t1),t2.begin(),test);
    
    for (int i=0;i<6;i++) 
        std::cout << t1[i];
}