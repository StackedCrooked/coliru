#include <string>

// Quiz: we have two variables with the same name
//       so why does the compiler not complain?

int main()
{
    std::string n(std::string());
    int n(int());
}