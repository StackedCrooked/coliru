// map::lower_bound/upper_bound
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include <iostream>
#include <map>
#include <vector>

int main ()
{
  std::map<int,int> matrix;
  std::pair<std::map<int,int>::iterator, std::map<int,int>::iterator> min_max;
  int min = 80;
  int max = 40;

  matrix[20]=20;
  matrix[40]=40;
  matrix[60]=60;
  matrix[80]=80;
  matrix[100]=100;
  //matrix.clear();

  if (max < min)
    std::cout << "ERROR: max < min\n"; 
  if (matrix.begin() == matrix.end())
    std::cout << "ERROR: matrix.begin() == matrix.end()\n"; 
  if (matrix.upper_bound(max) == matrix.begin())
    std::cout << "ERROR: upper_bound == matrix.begin()\n";
  if (matrix.lower_bound(min) == matrix.end())
    std::cout << "ERROR: lower_bound == matrix.end()\n";

  // for (std::map<int,int>::iterator it = matrix.begin(); it != matrix.end(); ++it) {
  for (auto& attribute : boost::adaptors::values(std::make_pair(matrix.lower_bound(min), matrix.upper_bound(max)))) {
    std::cout << attribute << '\n';
  }

  return 0;
}