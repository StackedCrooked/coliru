#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>

int main(){
    std::vector<int> v1 = {3,3,3,3}, v2 = {3,3,3,4};
    bool result = true;
    std::accumulate(v1.begin()+1, v1.end(), v1.front(),
        [&](int l, int r){ result = result && l == r; return r; }
    );
    std::cout << std::boolalpha << result;
}