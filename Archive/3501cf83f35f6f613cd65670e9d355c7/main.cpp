#include <algorithm>
#include <vector>

int main() {
    std::vector<int> v(200);
    std::iota(v.begin(),v.end(),1);
    v.resize(v.size()*3);
    auto it = v.end();
    v.insert(v.end(), v.begin(), it);
    v.insert(v.end(), v.begin(), it);
}