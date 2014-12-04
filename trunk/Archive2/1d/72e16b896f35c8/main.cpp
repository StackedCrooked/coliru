#include <iostream>
#include <string>


int main() {
    std::string s("abcdef");
    
    std::cout << s.rfind("f") << " " << s.rfind("") << " " << s.find_last_of("") << std::endl;
    std::cout << s.find("a") << " " << s.find("") << " " << s.find_first_of("") << std::endl;
    
    std::cout << s.find_first_not_of(s) << " " << s.find_last_not_of(s) << std::endl << std::endl;
    
    s.clear();
    
    std::cout << s.rfind("f") << " " << s.rfind("") << " " << s.find_last_of("") << std::endl;
    std::cout << s.find("a") << " " << s.find("") << " " << s.find_first_of("") << std::endl;
    
    std::cout << s.find_first_not_of(s) << " " << s.find_last_not_of(s) << std::endl;
    std::cout << s.find_first_not_of("a") << " " << s.find_last_not_of("a") << std::endl;
}