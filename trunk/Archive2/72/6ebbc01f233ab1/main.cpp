#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
template<class InputIterator, class Size, class OutputIterator>
  OutputIterator broken_copy_n (InputIterator first, Size n, OutputIterator result)
{
  while (n>0) {
    *result = *first;
    ++result; ++first;
    --n;
  }
  return result;
}

int main()
{
    std::istringstream iss("1 2 hello");
    std::copy_n(std::istream_iterator<int>(iss), 2, std::ostream_iterator<int>(std::cout, ", "));
    std::cout << "\nfailed? " << std::boolalpha << iss.fail() << "\n";
    
    std::istringstream iss2("1 2 hello");
    broken_copy_n(std::istream_iterator<int>(iss2), 2, std::ostream_iterator<int>(std::cout, ", "));
    std::cout << "\nfailed? " << std::boolalpha << iss2.fail() << "\n";
}