#include <algorithm>

int main()
{
    std::string s;
    std::max_element(s.begin(), s.end(),
                 [](auto a, auto b) { return true; });
}