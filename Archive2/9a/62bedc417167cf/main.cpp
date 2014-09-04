#include <iostream>

constexpr int log_level = 1; // just info

enum Levels
{
    INFO   = 1,
    ERROR  = 2,
};


template<enum Levels L, typename... Args>
    typename std::enable_if<(log_level >= L), void>::type 
    write_log(Args const & ... args)
    {   
        // really stupid switch/case
        switch(L) {
            case INFO:
                std::cout << "INFO:  Logging\n";
                break;
            case ERROR:
                std::cout << "ERROR: Logging\n";
                break;
        }
    }

/* SFINAE */
template<enum Levels L, typename... Args>
    typename std::enable_if<(log_level < L), void>::type
    write_log(Args const & ... args)
    { }



int main(void) 
{ 
    write_log<INFO>();
    write_log<ERROR>();  
}



