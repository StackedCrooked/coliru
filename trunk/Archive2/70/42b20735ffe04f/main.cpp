#include <iostream>
#include <map>
#include <unistd.h>
#include <string.h>

int main()
{  
    std::map<int,char> example = {{1,'a'},{2,'b'}};
 
    auto search = example.find(2);
    if(search != example.end()) {
        std::cout << "Found " << search->first << " " << search->second << '\n';
    }
    else {
        std::cout << "Not found\n";
    }
    char hostname[255];
    gethostname(hostname,255);
    std::cout << hostname;
}