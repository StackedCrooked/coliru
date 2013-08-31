#include <iostream>
#include <sstream>
 
void log(
        const char* argFile,
                int argLineNb,
                const char* argFunction,
                std::stringstream& argString) {
    std::cout << argFile << ":" << argLineNb << " " << argFunction
        << " " << argString.str()<< std::endl;
}
/**
 * \brief       Macro declarations
 */

#define LOG_TEST(f) \
                log(__FILE__, __LINE__, \
                        __FUNCTION__, (std::stringstream() << f))
            
int main(int argc, char** argv) {
    
    LOG_TEST("HELLO");
    LOG_TEST("HELLO" << " !");
    
    return 0;
}