#include <iostream>
#include <string>

template<typename... T>
void print(std::ostream& o, T&&... ts)
{
    int helper[] = {(o << ts, 0)...};
    (void)helper;
    o << std::endl;
}

int main()
{
    print(std::cout, 1, "2", std::string{"3"});
}