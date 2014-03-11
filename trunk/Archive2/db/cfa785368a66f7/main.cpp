#include <iostream>
#include <list>
#include <vector>
#include <array>
#include <random>
#include <algorithm>
#include <memory>

using namespace std;

class matrix {
  vector<vector<float>> data;
public:
  matrix() = default;
  matrix(matrix const& m) = default;
  matrix(matrix&& m) = default;
};

void use_and_free(std::unique_ptr<int[]> sink){}

int main() {
    matrix m1;
    matrix m2(m1);
    matrix m3(std::move(m1));

    auto ptr = std::unique_ptr<int[]>(new int[1000]);
//    use_and_free(ptr);
    use_and_free(std::move(ptr));
}