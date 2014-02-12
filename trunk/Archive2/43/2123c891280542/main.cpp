#include <iostream>
#include <sstream>
#include <cstring>
#include <iterator>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
    std::string input = "Why hello world";
    std::stringstream ss(input);
    std::istream_iterator<std::string> end;
    std::vector<std::string> vstrings(std::istream_iterator<std::string>(ss),
        std::istream_iterator<std::string>{});
    char** charArray = new char*[vstrings.size()];
    for (unsigned int i = 0; i < vstrings.size(); i++)
        charArray[i] = (char*)vstrings[i].c_str();
    for (unsigned int i = 0; i < vstrings.size(); i++)
        std::cout << charArray[i] << "\n";
    delete[] charArray;
}