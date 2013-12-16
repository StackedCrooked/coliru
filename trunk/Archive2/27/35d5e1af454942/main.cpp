#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <random>
#include <chrono>
#include <cctype>
#include <array>
#include <algorithm>
#include <map>
#include <type_traits>

int main(int argc, char* argv[])
{
    std::string valid_ident_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_";
    unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
    
    std::minstd_rand0 g1 (seed1);
    std::uniform_int_distribution<int> dist(0, valid_ident_chars.size()-1);
    auto get_random_char = [&] () -> char {
        return valid_ident_chars[dist(g1)];
    };
    
    auto generate_ident = [&] (int ident_length) -> std::string {
        int ident_index = 0;
        std::string final = "";
        while (true) {
           char current = get_random_char();
           if (ident_index == 0 && isdigit(current)) continue;
           
           final += current;
           
           ident_index++;
           if (ident_index >= ident_length) break;
        }
        return final;
    };
    
    std::array<std::string, 5> types = {
        "int",
        "float",
        "double",
        "std::string",
        "char"
    
    };
    
    std::cout << "#include <iostream>" << std::endl;
    std::cout << "#include <type_traits>" << std::endl;
    std::cout << std::endl;

    
    unsigned seed2 = std::chrono::system_clock::now().time_since_epoch().count();
    std::minstd_rand0 g2 (seed2);
    std::uniform_int_distribution<int> dist2(0, types.size()-1);
    
    struct Variable {
        std::string name;
        std::string type;
    };
    
    std::vector<Variable> variables;
    
    for (int i = 0; i < 10; i++) {
        std::string type = types[dist2(g2)];
        variables.push_back(Variable{generate_ident(10), type});
        int field_width = std::max_element(types.begin(), types.end())->size();
        std::cout << std::setw(field_width) << std::left << type << " " << variables[variables.size()-1].name << " = " << type << "();" << std::endl;
    }
    
    std::cout << std::endl;
    
    std::cout << "    template <typename A, typename B>\n\
    typename std::enable_if<std::is_convertible<A, B>::value, decltype(A() + B())>::type\n\
        try_to_add(A a, B b) {\n\
            return a + b;\n\
        }" << std::endl;
        
    std::cout << "int main(int argc, char* argv[]) {" << std::endl;
    
    for (int i = 0; i < variables.size()/2; i+=1) {
        std::cout << "\ttry_to_add<" << variables[i].type << "," << variables[i+1].type << ">(" << variables[i].name << "," << variables[i+1].name << ");" << std::endl;
        std::cout << std::endl;
    }
    
    std::cout << std::endl;
    std::cout << "\treturn 0;" << std::endl;
    std::cout << "}" << std::endl;
    
    return 0;
}
