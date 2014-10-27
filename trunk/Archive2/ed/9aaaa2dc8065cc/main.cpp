#include <iostream>
#include <initializer_list>

int main()
{
    operator<<(std::cout, (auto i = {1, 2, 3}).size());
}
