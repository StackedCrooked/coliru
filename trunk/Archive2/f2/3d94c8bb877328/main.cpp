#include <sstream>
#include <iostream>

int main(int argc, char** argv)
{
    if (argc>1)
    {
        std::istringstream is(argv[1]);
        std::string out("__INIT__");
        is >> out;
        std::cout << "good:"  << is.good() << " fail:"<< is.fail() << " eof:" << is.eof() << std::endl;
        std::cout << "value:" << out << std::endl;
    }
}