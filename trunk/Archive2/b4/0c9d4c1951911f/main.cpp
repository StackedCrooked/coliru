#include <map>
#include <unordered_map>
#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;
using namespace std::placeholders;


struct my_equal_cmp {
    bool operator() (char a,char b) {
        return a==b;
    }
};

int main()
{
    unordered_map<char, int, std::hash<char>, std::equal_to<char> >    default_dict;
    
    
    // uses bool my_equal_cmp(char,char);
    unordered_map<char, int, std::hash<char>, my_equal_cmp >    custom_dict;

}