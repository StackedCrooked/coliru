#include <iostream>

int main(int argc, char* argv[])
{
    std::cout << "The name of this program is: " << argv[0];
    std::cout << "\nAdditional arguments (if any) passed to this program:\n";
    for (int i = 1; i < argc; ++i)
        std::cout << argv[i] << '\n';
}