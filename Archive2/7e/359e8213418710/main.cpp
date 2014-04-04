#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstddef>


template <typename Func>
void
log (Func const & log_line_func)
{
    
}


int main()
{
    auto f = [&](char const * _func) {
        std::stringstream ss;
        ss << _func << ": " << x;
    };
    log (f);
}