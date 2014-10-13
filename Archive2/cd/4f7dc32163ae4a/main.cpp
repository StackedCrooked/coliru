#include <string>

using ResponseCallback = void (std::string const&);

ResponseCallback myFunc;

int main()
{
    myFunc("hello world");
}

void myFunc(std::string const&) {}