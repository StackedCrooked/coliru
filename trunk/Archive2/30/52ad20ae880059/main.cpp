#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::copy(words.begin(), words.end(), std::ostream_iterator<std::string>(std::cout, " "));
}
