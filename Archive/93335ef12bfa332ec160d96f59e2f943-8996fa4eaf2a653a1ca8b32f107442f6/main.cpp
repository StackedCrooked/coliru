#include <string>
#include <iostream>

namespace X {
   struct XX {
        static const std::string str1;
        static const std::string str2;
   };
}

namespace X {
    const std::string XX::str1 = "Hello World";
    const std::string XX::str2  = "Hello Country";
}

int f(std::string str)
{
    std::cout << str;
}

int main()
{
    f(X::XX::str1);
}