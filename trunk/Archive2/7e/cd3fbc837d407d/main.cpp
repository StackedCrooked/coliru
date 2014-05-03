#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>

std::string Interpolate(std::string raw_string) {
    std::size_t found = raw_string.find_first_of("%");
    if(found != std::string::npos && raw_string[found-1] != '\\') {
        std::cout << "Throw cs540::ArgsMismatchException" << std::endl;
    }
    return raw_string;
}


template <typename T, typename ...Args>
std::string Interpolate(std::string raw_string, T arg_head, Args... arg_tail) {
    std::size_t found = raw_string.find_first_of("%");
    while(found != 0 && raw_string[found-1] == '\\') {
        found = raw_string.find_first_of("%", found + 1);
    }
    if(found == std::string::npos) {
        std::cout << "Throw cs540::ArgsMismatchException." << std::endl;
    }

    // Checking the typeid of the arg_head, and converting it to a string, and concatenating the strings together. 
    else {
        if(std::is_arithmetic<T>::value) { 
            raw_string = raw_string.substr(0, found) + std::to_string(arg_head) + raw_string.substr(found + 1, raw_string.size());
        }
    }
    return Interpolate(raw_string, arg_tail...);
}

int main(void) {
    int i = 24332;
    float x = 432.321;
    std::string str1("foo");
    //Works
    std::cout << Interpolate(R"(goo % goo % goo)", i, x) << std::endl;
    // Does not work, even though I'm not actually doing anything with the string argument
    std::cout << Interpolate(R"(goo %)", str1) << std::endl;
}