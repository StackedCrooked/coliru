//excercise to specialize function

#include <iostream>
#include <string>

template <typename T>
std::ostream &println(std::ostream &output, const T &val) {
    output << val << std::endl;
    return output;
}

template<>
std::ostream &println<std::string>(std::ostream &output, const std::string &val) {
    output << "cannot print a string" << std::endl;   
    return output;
}

int main() {
    println(std::cout, "Ufuoma");
    println(std::cout, std::string("Ufuoma"));
}