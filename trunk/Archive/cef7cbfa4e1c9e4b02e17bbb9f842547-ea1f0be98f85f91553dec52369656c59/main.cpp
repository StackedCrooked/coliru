#include <iostream>
#include <unordered_map>

bool add(std::istream& input, int& last_result) {
    int left, right;
    if (input >> left >> right) { 
        last_result = left+right;
        return true;
    }
    //otherwise, error
    return false;
}
bool mul(std::istream& input, int& last_result) {
    int left, right;
    if (input >> left >> right) { 
        last_result = left*right;
        return true;
    }
    //otherwise, error
    return false;
}
bool sub_prev(std::istream& input, int& last_result) {
    int right;
    if (input >> right) {
        last_result = last_result - right;
        return true;
    }
    //otherwise, error
    return -1;
}

int main() {
    typedef bool(*command_type)(std::istream&,int&);
    const std::unordered_map<std::string, command_type> commands = {
            {"add", add},
            {"mul", mul},
            {"sub_prev", sub_prev},
        };
    
    int num_commands;
    std::string operation;
    while(std::cin >> num_commands) { //read all the input
        int result = 0;
        for(int i=0; i<num_commands; ++i) { //for each command 
            if (std::cin >> operation) { //read in the command
                auto iterator = commands.find(operation);
                if (iterator == commands.end()) { //command doesn't exist
                    std::cerr << operation << " isn't a valid command\n";
                } else { //we found the command! DO IT
                    command_type cur_command = iterator->second;
                    if(cur_command(std::cin, result)) { //if command worked
                        std::cout << "The result of the operation is " << result << '\n';
                    } else {
                        std::cout << "The operation failed!\n";
                    }                   
                }
            }
        }
    }
}