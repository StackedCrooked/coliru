#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>

struct thingy {
    std::stringstream data;
};

int main() {
    thingy message;
    message.data.str("afda51df3s3agf4gfgdag2f3dsghf4ds5g");
    message.data.seekg(0);
    
    
    std::vector<char> buffer(std::istream_iterator<char>(message.data),std::istream_iterator<char>());
    std::cout << buffer.data();
}