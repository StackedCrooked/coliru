#include <vector> // vector
#include <algorithm> // std::copy
#include <iterator>  // std::back_inserter and std::istream_iterator
#include <sstream>   // std::istringstream
#include <iostream>  // std::cout

int main()
{
    std::string line = "1 2 3 4 5 6 8 120";
    std::istringstream iss(line);

    std::vector<int> ints;
    std::copy(std::istream_iterator<int>(iss), {}, std::back_inserter(ints));

    std::cout << "parsed " << ints.size() << " integers: ";
    std::copy(ints.begin(), ints.end(), std::ostream_iterator<int>(std::cout, ";"));
}
