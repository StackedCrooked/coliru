#include <iostream>
#include <utility>
#include <sstream>
#include <string>

std::pair <std::string, std::string> parse_command(const std::string  &command) {
    std::istringstream iss(command);
    
    
    std::string func;
    std::getline(iss, func, '('); // get the function name

    std::string params;
    std::getline(iss, params, ')'); // get the parameters for the function
    
    return std::pair<std::string, std::string> (std::move(func), std::move(params));
}

int main()
{
    std::pair <std::string, std::string> parsed = parse_command("DB.Add.User(abc)");
    std::cout << "Function to call: \'" << parsed.first << "\' " 
              << " <===> Parameter to use \'" << parsed.second << '\'' << std::endl;
    return 0;
}