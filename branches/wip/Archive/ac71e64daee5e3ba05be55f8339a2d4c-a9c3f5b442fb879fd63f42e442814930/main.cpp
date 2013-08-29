#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>

bool test(std::vector<int> const& v){
    bool result = true;
    std::accumulate(v.begin()+1, v.end(), v.front(),
        [&](int l, int r){ result = result && l == r; return r; }
    );
    std::cout << std::boolalpha << result << "\n";
}

int main(){
    std::vector<int> v1 = {3,3,3,3}, v2 = {3,3,4,3};
    test(v1);
    test(v2);
}