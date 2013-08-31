#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

int main()
{
    std::vector<std::string> input = { "unsorted", "containing", "optional", "unsorted", "duplicate", "duplicate", "values" };

    std::sort(begin(input), end(input));

    std::unique_copy(begin(input), end(input), std::ostream_iterator<std::string>(std::cout, " "));

    std::cout << "\n";
}