#include <string>
#include <sstream>
#include <string>

int main()
{
    std::ostringstream oss;
    oss << "Hello work" << std::endl;

    const char *charPtr = oss.str().c_str(); // Unexpected results

    std::string str = oss.str();
    const char *charPtr2 = str.c_str(); // OK

    return 0;
}