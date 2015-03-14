#include <string>

int main()
{
    std::string str{"123"};
    auto it = str.begin();
    --it;
    ++it; // Does *it point to character '1' now?
}