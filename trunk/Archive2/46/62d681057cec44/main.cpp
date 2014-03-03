#include <iostream>

int main()
{
    int hours, minutes;
    char colon;
    std::cin >> hours >> colon >> minutes;
    std::cout << hours << " : " << minutes;

    return 0;
}