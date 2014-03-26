#include <memory>
#include <vector>

int main() {
    std::vector<int, std::allocator<double>> x;
    x.push_back(100);
    x.push_back(100);
    x.push_back(100);
    x.push_back(100);
    x.push_back(100);
    x.push_back(100);
    x.push_back(100);
}