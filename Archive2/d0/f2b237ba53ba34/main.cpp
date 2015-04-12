#include <iostream>
#include <map>
#include <string>

enum Errors {ErrorA=0, ErrorB, ErrorC};

std::ostream& operator<<(std::ostream& out, const Errors value){
    static std::map<Errors, std::string> strings;
    if (strings.size() == 0){
#define INSERT_ELEMENT(p) strings[p] = #p
        INSERT_ELEMENT(ErrorA);     
        INSERT_ELEMENT(ErrorB);     
        INSERT_ELEMENT(ErrorC);             
#undef INSERT_ELEMENT
    }   

    return out << strings[value];
}

int main(int argc, char** argv){
    std::cout << ErrorA << std::endl << ErrorB << std::endl << ErrorC << std::endl;
    return 0;   
}