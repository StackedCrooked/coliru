#include <memory>
#include <vector>

int main(){
    std::vector<std::unique_ptr<int>> v;
    v.push_back(std::unique_ptr<int>(new int(5)));
    v.resize(10);
}