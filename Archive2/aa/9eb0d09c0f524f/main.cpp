#include <iostream>
#include <vector>
//#include <algorithm>

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::string lh = "localhost";
    auto it = std::find(words.begin(), words.end(), lh);
}
