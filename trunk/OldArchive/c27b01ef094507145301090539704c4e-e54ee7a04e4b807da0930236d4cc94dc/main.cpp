#include <string>
#include <iostream>

int main() {

    std::string s_str = "Hello World";
    std::string *p_str = &s_str;
    
    std::cout << s_str << " " << *p_str;
    
    free(p_str);
}
