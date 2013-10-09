#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <algorithm>
int main()
{
    std::ifstream is("d:\\temp\\DataFile2.txt");
    std::vector<int> numbers(std::istream_iterator<int>(is), std::istream_iterator<int>());
    std::copy(numbers.begin(), numbers.end(),
    std::ostream_iterator<double>(std::cout, " "));
    return 0;
}