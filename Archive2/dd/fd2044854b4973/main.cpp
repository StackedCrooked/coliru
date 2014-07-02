#include <algorithm>
#include <iomanip>
#include <iostream>

#include <boost/multi_array.hpp>

int main()
{
  // helper type for a 2d matrix of ints
  using array_type = boost::multi_array<int, 2>;

  array_type a(boost::extents[4][3]);   // 4x3 matrix
  array_type b(boost::extents[2][3]);   // 2x3 matrix

  // fill the matrices
  std::iota(a.data(), a.data() + a.num_elements(), 0);
  std::iota(b.data(), b.data() + b.num_elements(), 20);

  auto array_printer = [](array_type const& arr) {
    for(auto const &row : arr) {
      for(auto const& elem : row) {
        std::cout << std::setw(2) << elem << ' ';
      }
      std::cout << '\n';
    }
    std::cout << '\n';
  };

  std::cout << "Before:\na =\n";
  array_printer(a);
  std::cout << "b =\n";
  array_printer(b);

  using range_type = boost::multi_array_types::index_range;
  using view_type = array_type::array_view<2>::type;

  // Create a 2d view of a 
  //  - the rows of the view consist of rows [0, 3) with a stride of 2
  //  - the columns of the view consist of all columns of a
  view_type a_view = a[boost::indices[range_type(0,3,2)][range_type()]];

  a_view = b;
  std::cout << "After:\na =\n";
  array_printer(a);
}
