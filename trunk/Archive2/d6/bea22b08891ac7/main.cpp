#include <limits>
#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <sstream>

inline std::string lexical_cast(const float& arg)
{
        std::stringstream ss;
        ss << std::setprecision(std::numeric_limits<float>::digits10) << arg;
        if (!ss)
                throw 0;

        return ss.str();
}

int main()
{
        std::cout << std::numeric_limits<float>::digits10 << '\n';
        std::cout << lexical_cast(0.000012345678) << '\n';
}
