#include <iostream>
#include <string>
#include <regex>

using namespace std;

int main()
{
    string str = "regex does something really12regex3happened 00this is a test regex";
    regex rx("ex");
    
    vector<int> matches; 
    
    for(auto iterator = std::sregex_iterator(str.begin(),str.end(), rx); 
        iterator != std::sregex_iterator(); 
        ++iterator){
            matches.push_back(iterator->position());
    }
    
    for(int n: matches)
    {
        std::cout << n << endl;
    }
}