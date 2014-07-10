#include <iostream>
#include <boost/predef.h>

using namespace std;

int main() {
	if(BOOST_OS_WINDOWS)
        std::cout << "Windows" << std::endl;
    else if(BOOST_OS_LINUX)
        std::cout << "Linux" << std::endl;
    else
        std::cout << "Other" << std::endl;
}