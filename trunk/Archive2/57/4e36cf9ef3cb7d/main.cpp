#include <string>
#include <iostream>

void parse(const std::string& str) {
    size_t offset = 0;
    auto pos = str.find(',');
    while(pos != str.npos) {
        auto end = str.find_first_of("\r\n", offset);
        std::string x(&str[pos + 1], &str[end]);
        std::cout << std::stoi(std::string{&str[offset], &str[pos]}) << "~" << x << ";";
//        if(end != str.npos) {
            offset = end + 2;
//        }
        pos = str.find(',', offset);
    }
}

int main() {
    std::string raw = "1,myfilename1.txt\r\n3,myfilename2.txt\r\n2,myfilename2.txt\r\n";
    parse(raw);
}