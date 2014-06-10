#include <vector>
#include <string>
#include <iostream>

std::vector<std::vector<std::string>> LoadClasses();

template <typename T>
std::ostream &operator << (std::ostream &oss , const std::vector<T> &array) {
    for (auto &v : array) {
        oss << v << ' ';
    }
    return oss << '\n';
}

int main() {
    std::cout << LoadClasses();
    return 0;
}

        

std::vector<std::vector<std::string>> LoadClasses() {
    
    std::vector<std::string> keywords = {"keyword:", "global", "local", "as", "bool", "decimal", "number", "text"};
    std::vector<std::string> operators = {"operator:", "=", "\\+", "-", "\\*", "\\/", "\\^"};
	std::vector<std::string> boolean = {"bool:", "true", "false"};
	std::vector<std::string> number = {"number:", "\\d"};
	std::vector<std::string> decimal = {"decimal:", "\\d+(\\.\\d)?"};
	std::vector<std::string> whitespace = {"whitespace:", "\\s"};
	std::vector<std::string> identifier = {"identifier:", "[a-zA-Z_][a-zA-Z_0-9]*"};
    
    return std::vector<std::vector<std::string>> /*Notice same type as function type */
    {
        keywords, operators, boolean, number, decimal, whitespace, identifier
    };
}
    