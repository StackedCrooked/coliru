#include <iostream>
#include <vector>

int main() {
    using std::vector;
    
    int n = 1;
    vector<vector<int > > matrix(n+2, vector<int> (n+2, -1));    
    
    for (const auto &vec : matrix) {
        for (auto i : vec) {
            std::cout << i << ' ';
        }
        
        std::cout << '\n';
    }
}
