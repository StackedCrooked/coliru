#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::cout;
using std::endl;
using std::vector;

const char DELIMITER = ' ';

void tokenize(std::string str, std::vector<string> &token_v){
    size_t start = str.find_first_not_of(DELIMITER), end=start;

    while (start != std::string::npos){
        // Find next occurence of delimiter
        end = str.find(DELIMITER, start);
        // Push back the token found into vector
        token_v.push_back(str.substr(start, end-start));
        // Skip all occurences of the delimiter to find new start
        start = str.find_first_not_of(DELIMITER, end);
    }
}

int main(){
   string s = "   A B  C  D  E    F      ";
   vector<string> v;
   tokenize(s, v);
   for (string str : v){
     cout << str << endl;
   }
   cout << "The end" << endl;
}
