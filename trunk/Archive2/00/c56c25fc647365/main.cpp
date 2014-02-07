#include <iostream>
#include <sstream>
#include <cstring>
#include <iterator>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
    std::string input = "Why hello world";
    std::string s = "What is the right way to split a string into a vector of strings";
    std::stringstream ss(s);
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    std::vector<std::string> vstrings(begin, end);
    const char** charArray = new char*[vstrings.size()];
    std::copy(vstrings.begin(), vstrings.end(), &charArray[0]);

}