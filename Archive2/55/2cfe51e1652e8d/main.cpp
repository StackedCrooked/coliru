#include <algorithm>
#include <iostream>
#include <boost/multi_array.hpp>

int main () {
  boost::multi_array<double,3> A(boost::extents[3][4][2]);

  std::fill_n(A.origin(), A.num_elements(), 1);

  std::cout << "filled with 1s: \n";
  for(int i = 0; i != 3; ++i)  {
    for(int j = 0; j != 4; ++j) {
      for(int k = 0; k != 2; ++k)
        std::cout << A[i][j][k] << ' ';
      std::cout << '\n';
    }
    std::cout << '\n';
  }

  std::fill_n(A.origin(), A.num_elements(), 0);

  std::cout << "filled with 0s: \n";
  for(int i = 0; i != 3; ++i)  {
    for(int j = 0; j != 4; ++j) {
      for(int k = 0; k != 2; ++k)
        std::cout << A[i][j][k] << ' ';
      std::cout << '\n';
    }
    std::cout << '\n';
  }
}
