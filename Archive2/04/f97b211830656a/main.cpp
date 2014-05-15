#include <iostream>
#include <map>
#include <unordered_map>
 
 using namespace std;
 
int main()
{  
    std::map<int,char> map_ex;
    map_ex.insert({{1,'a'},{2,'b'}});
    char search = map_ex[1];
    if(search != map_ex.end()) {
        std::cout << "Found " << search->first << " " << search->second << "\n";
    }
    else {
        std::cout << "Not found" << std::endl;
    }
    return 0;
}