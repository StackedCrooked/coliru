#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>

struct thingy {
    std::istream& data;
};

int main() {
    std::stringstream raw("afda51df3s3agf4gfgdag2f3dsghf4ds5g");
    raw.seekg(0);
    
    thingy message {raw};
    
    
    std::vector<char> buffer(std::istream_iterator<char>(message.data),std::istream_iterator<char>());
    std::cout << buffer.data();
}