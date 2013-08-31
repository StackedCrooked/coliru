#include <vector>
#include <memory>


int main() {
    std::vector<std::unique_ptr<int>> v = {
        std::unique_ptr<int>(new int), std::unique_ptr<int>(new int), std::unique_ptr<int>(new int)
    };
    
    /*
    // BELOW WORKS
    std::vector<std::unique_ptr<int>> v;
    for(int i = 0; i < 3; ++i) {
        v.push_back(std::unique_ptr<int>(new int));
    }
    */
}