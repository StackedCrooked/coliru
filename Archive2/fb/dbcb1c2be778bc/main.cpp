#include <iostream>
#include <string>
#include <sstream>


int main()
{
    // Redirect cout
    // http://stackoverflow.com/a/6211644/796832
    std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
	std::ostringstream strCout;
	std::cout.rdbuf(strCout.rdbuf());
    
    
    std::cout << "asdf" << std::endl;
    std::cout << "qwer" << std::endl;
    
    
    // How do I transform `strCout` to append something to each cout call?
    
    
    /* */
    // Restore old cout.
    std::cout.rdbuf(oldCoutStreamBuf);
    
    // Will output our transformed cout from above.
    std::cout << strCout.str();
    /* */
    
    return 0;
}

