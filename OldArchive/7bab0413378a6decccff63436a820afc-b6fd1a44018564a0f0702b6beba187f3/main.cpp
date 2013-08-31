#include <vector>       // for vector
#include <iostream>     // for cout/cin, streamsize
#include <sstream>      // for istringstream
#include <algorithm>    // for copy, copy_n
#include <iterator>     // for istream_iterator<>, ostream_iterator<>
#include <limits>       // for numeric_limits

int main()
{
    std::vector<std::vector<double>> contents;

    int number;
    while (std::cin >> number)
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // skip eol
        std::string line;
        std::getline(std::cin, line);
        if (std::cin)
        {
            contents.emplace_back(number);
            std::istringstream iss(line);
            std::copy_n(std::istream_iterator<double>(iss), number, contents.back().begin());
        }
        else
        {
            return 255;
        }
    }

    if (!std::cin.eof())
        std::cout << "Warning: end of file not reached\n";

    for (auto& row : contents)
    {
        std::copy(row.begin(), row.end(), std::ostream_iterator<double>(std::cout," "));
        std::cout << "\n";
    }
}
