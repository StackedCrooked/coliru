#include <string>
#include <iostream>
 
int main() {
    std::basic_string<char> str = "string";
    const char* cptr = "C-string";
    const char carr[] = "Two and one";
 
    std::string output;
 
    // 1) Repeat a char
    output.append(3, '*');
    std::cout << "1) " << output << "\n";
 
    //  2) Append a whole string
    output.append(str);
    std::cout << "2) " << output << "\n";
 
    // 3) Append part of a string (last 3 letters, in this case)
    output.append(str, 3, 3);
    std::cout << "3) " << output << "\n";
 
    // 4) Append part of a C-string
    // Notice, because `append` returns *this, we can chain calls together
    output.append(1, ' ').append(carr, 4);
    std::cout << "4) " << output << "\n";
 
    // 5) Append a whole C-string
    output.append(cptr);
    std::cout << "5) " << output << "\n";
 
    // 6) Append range
    output.append(&carr[3], std::end(carr));
    std::cout << "6) " << output << "\n";
 
    // 7) Append initializer list
    output.append({ ' ', 'l', 'i', 's', 't' });
    std::cout << "7) " << output << "\n";
}