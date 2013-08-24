#if 0
echo "Compile $0"
g++ -o MildForkBomb $0
exit
#endif

#include <unistd.h>
#include <iostream>

int main()
{
    std::cerr << "<PAIR>"  << std::endl;
    std::cerr << "<FORK>"  << std::endl;
    std::cerr << fork()    << std::endl;
    std::cerr << "</FORK>" << std::endl;

    std::cerr << "<FORK>" << std::endl;
    std::cerr << "<PAIR>"  << std::endl;
    std::cerr << "<FORK>"  << std::endl;
    std::cerr << fork()    << std::endl;
    std::cerr << "</FORK>" << std::endl;
}
