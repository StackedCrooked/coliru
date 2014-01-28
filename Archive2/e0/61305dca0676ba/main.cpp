#include <iostream>
#include <regex>

int main(void)
    {
    const char* Pattern = "^(%%)|";
    std::regex Machine;

    try {
        Machine = Pattern;
        }
    catch(std::regex_error e)
        {
        std::cerr << "regex could not compile pattern: "
          << Pattern << "\n"
          << e.what() << std::endl;
        throw;
        }

    return 0;
    }