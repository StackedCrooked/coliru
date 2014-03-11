#include <iostream>
#include <list>
#include <vector>
#include <array>

using namespace std;

array<int, 3> add_vec(array<int, 3> const& a,
                      array<int, 3> const& b) {
  return {{a[0] + b[0], a[1] + b[1], a[2] + b[2]}};
}

int main() {
  list<int> primes = {2, 3, 5, 7, 11, 13, 17, 19};
  vector<vector<int>> matrix = {{1, 2, 3},
                                {4, 5, 6},
                                {7, 8, 9}};
}