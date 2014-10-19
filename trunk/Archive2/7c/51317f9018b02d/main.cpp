#include <iostream>
#include <map>
 
int main()
{  
    std::multimap<int,char> example = {{1,'a'},{2,'b'},{3,'c'},{3,'d'}};
 
    auto search = example.find(3);
    while(search != example.end()) {
        std::cout << "Found " << search->first << " " << search->second << '\n';
        search++;
    }
    //else {
    //    std::cout << "Not found\n";
    //}
}