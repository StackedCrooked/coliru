#include <string>

int main()
{
    auto f = [](std::string const& a){ return [a](std::string const& b) { return a == b; }; };
}
