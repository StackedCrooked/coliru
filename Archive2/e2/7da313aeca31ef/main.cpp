#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <string>
#include <memory>
#include <deque>
#include <cstring>
#include <array>

#include <cstdlib>//strtol
#include <climits>//LONG_MAX, LONG_MIN

//Affichage
using std::cout;

//Conteneur
using std::vector;
using std::string;
using std::map;
using std::set;
using std::shared_ptr;
using std::unordered_map;
using std::deque;
using std::multimap;

int main() {
    cout << "debut\n";
    
    multimap<string, int> mmap= {{"a", 1}, {"b", 2}, {"a",3}};
    
    cout << "count: " << mmap.size();
    
    cout << "fin\n";
    return 0;
}