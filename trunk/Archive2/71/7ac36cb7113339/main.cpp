#include <locale>
#include <iostream>

struct token_ctype : std::ctype<char> {
    token_ctype(): std::ctype<char>(token_table()) {}
    static const mask* token_table() {
        static mask result[table_size];
        result['('] = std::ctype_base::space;
        result[')'] = std::ctype_base::space;
        result[' '] = std::ctype_base::space;
        result['\n'] = std::ctype_base::space;
        result['='] = std::ctype_base::space;
        result['+'] = std::ctype_base::space;
        return result;
    }
};

#include <sstream>

int main() {
    std::string test = "(23567)=(58765)+(67888)+(65678)";
    std::stringstream ss(test);
    ss.imbue(std::locale(ss.getloc(), new token_ctype));
    for(std::string x; ss >> x; ) {
        std::cout << x << '\n';
    }
}