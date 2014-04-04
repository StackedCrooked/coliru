#include <iostream>
#include <iterator>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <string>
#include <locale>
#include <vector>
#include <stdexcept>

// http://stackoverflow.com/a/1895584/2089675
struct csv_reader: std::ctype<char> {
    csv_reader(): std::ctype<char>(get_table()) {}
    static std::ctype_base::mask const* get_table() {
        static std::vector<std::ctype_base::mask> rc(table_size, std::ctype_base::mask());

        rc[','] = std::ctype_base::space;
        rc['\n'] = std::ctype_base::space;
        rc[' '] = std::ctype_base::space;
        return &rc[0];
    }
};

int main()
{
    std::string test("Hello,34,565,What,is,89");
    std::istringstream iss(test);
    iss.imbue(std::locale(std::locale(), new csv_reader()));
    
    // http://stackoverflow.com/a/237280/2089675
    std::copy_if(std::istream_iterator<std::string>(iss),
                 std::istream_iterator<std::string>(),
                 std::ostream_iterator<std::string>(std::cout, ","),
                 [](const std::string &word)->bool {
                     try {
                         std::stoi(word);
                         return true;
                     }
                     catch (const std::logic_error& le){}
                     return false;
                 });
    
    return 0;
}