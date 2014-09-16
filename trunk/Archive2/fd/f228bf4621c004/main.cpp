#include <boost/format.hpp>
#include <utility>
#include <string>
#include <iostream>

std::string awesome_printf_helper(boost::format& f){
    return boost::str(f);
}

template<class T, class... Args>
std::string awesome_printf_helper(boost::format& f, T&& t, Args&&... args){
    return awesome_printf_helper(f % std::forward<T>(t), std::forward<Args>(args)...);
}

template<typename... Arguments>
void awesome_printf(std::string const& fmt, Arguments&&... args)
{
    boost::format f(fmt);
    std::cout << awesome_printf_helper(f, std::forward<Arguments>(args)...) << std::endl;
}

int main() {
    awesome_printf("%1% %2% %3% %2% %1% \n",  "o", "oo", "O");
}