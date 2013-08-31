#include <iostream>

int get_column_index(const std::string & name)
{
    int result = 0;
    auto count = 'Z' - 'A' + 1;
    for (auto c : name)
    {
        result *= count;
        result += c - 'A' + 1;
    }
    return result;
}

int main()
{
    std::cout << get_column_index("A") << std::endl;
    std::cout << get_column_index("Z") << std::endl;
    std::cout << get_column_index("AA") << std::endl;
    std::cout << get_column_index("AB") << std::endl;
    std::cout << get_column_index("AAA") << std::endl;
}