#include <iostream>
#include <string>

void show_list(){}

template<typename T>
void show_list(const T& value)
{
    std::cout << value << endl;
}

template<typename T, typename... Args>
void show_list(const T& value, const Args&... args)
{
    std::cout << value << ", ";
    show_list(args...);
}

int main()
{
    show_list(14, 2.71828, "Mr String objects!");
    return 0;
}