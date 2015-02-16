#include <sstream>
#include <iostream>

template<typename Value, typename... Values>
std::string to_csv2 ( Value v, Values... vs )
{
    std::ostringstream oss;
    using expander = int[];
    oss << v; // first
    (void) expander{ 0, (oss << ";" << vs, void(), 0)... };
    return oss.str();
}
    
int main(){
    std::cout << to_csv2(1,"Hello",3) << std::endl;
}