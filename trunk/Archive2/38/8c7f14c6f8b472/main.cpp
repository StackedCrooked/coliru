#include <iostream>
#include <map>
 
int main()
{  
    std::map<int,char> example = {{1,'a'},{2,'b'}};
    system("echo $PATH");
    auto search = example.find(2);
    if(search != example.end()) {
        std::cout << "Found " << search->first << " " << search->second << '\n';
    }
    else {
        std::cout << "Not found\n";
    }
}