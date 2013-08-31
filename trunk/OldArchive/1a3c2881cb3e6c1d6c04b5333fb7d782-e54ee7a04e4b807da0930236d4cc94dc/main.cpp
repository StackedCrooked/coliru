#include <iostream>
#include <vector>
int main() {
    using std::vector;
    int const n = 2;
    vector<vector<int > > matrix(n+2, vector<int> (n+2, -1));
    for (auto&& row : matrix) {
        for (auto&& element : row) {
            std::cout << element << " ";
        }
        std::cout << "\n";
    }
}
