#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

constexpr unsigned faculty(unsigned n) {
  return (0 == n) ? 1 : n * faculty(n - 1);
}

int main() {
    std::array<int, 3> a = {{1,2,3}};
    std::array<int, 3> perm[faculty(a.size())];

    for (auto& p : perm) {
      p = a;
      std::next_permutation(begin(a), end(a));
    }
    
    for (auto const& p : perm) {
        for (auto i: p) {
            cout << i;
        }
        cout << endl;
    }
    
}