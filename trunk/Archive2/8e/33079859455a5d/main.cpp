#include <iostream>
#include <limits>

int main()
{
    std::cout << "double_max = " << std::numeric_limits<double>().max() << std::endl;
    std::cout << "double_min = " << std::numeric_limits<double>().min() << std::endl;
    std::cout << "float_max = " << std::numeric_limits<float>().max() << std::endl;
    std::cout << "float_min = " << std::numeric_limits<float>().min() << std::endl;
}

