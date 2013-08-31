#include <string>
#include <sstream>

int main()
{
    float value;
    std::string stringNum = "0.5";
    std::istringstream(stringNum) >> value;

    return 0;
}
