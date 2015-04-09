#include <vector>
#include <iterator>

int main(){
    std::vector<int> v = {1, 2, 3};
    v.erase(v.rbegin());
}