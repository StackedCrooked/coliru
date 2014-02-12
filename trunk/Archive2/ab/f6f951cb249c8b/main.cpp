#include <sstream> 
#include <iterator> 
#include <algorithm>
#include <iostream>

using namespace std;
int main(int argc, char *argv[]) {
    std::vector<std::string> output;
    std::string sen = "Go over there";
    std::string word = "";
    unsigned int len = 0;
    for (const auto& c : sen) {
        ++len;
        if (c == ' ' || len == sen.size()) {
            if (len == sen.size())
                word += c;
            output.push_back(word);
            word = "";
        }
        if (c != ' ')
            word += c;
    }
    std::ostringstream oss;
    std::copy(output.rbegin(), output.rend(), std::ostream_iterator<std::string>(oss, " "));
    sen = oss.str();
    sen.pop_back(); // Get rid of last space, C++11 only
    std::cout << sen;
}