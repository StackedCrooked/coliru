#include<vector>
#include <utility>
int main() { 
    std::vector<int> v(1000);
    v = std::move(v);
    return v.size();
}