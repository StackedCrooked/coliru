#include <algorithm>
#include <array>
#include <iostream>
#include <vector>


int main(){
    int a=54;
    std::vector<std::reference_wrapper<const int>> res;
    res.push_back(a);

}