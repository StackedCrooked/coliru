#include <iostream>
#include <fstream>
int main()
{
    std::ifstream f("doesn't exist");
    try {
        f.exceptions(f.failbit);
    } catch (const std::ios_base::failure& e)
    {
        std::cout << "Caught an ios_base::failure.\n"
                  << "Explanatory string: " << e.what() << '\n'
                  << "Error code: " << e.code() << '\n';
    }
}