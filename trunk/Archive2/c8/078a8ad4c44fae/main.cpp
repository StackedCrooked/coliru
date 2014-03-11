#include <iostream>
#include <unordered_map>
#include <random>
 
using namespace std;

#define SEED 3141592654
 
int main()
{  
    std::unordered_map<long, bool> map;
    bool OK = true;
    for (int e = 1; e <= 100; e++) {
        for (int i = 1; i <= 100; i++) {
          long x = SEED * e + i;
          unordered_map<long, bool>::const_iterator search = map.find(x);
          if (search != map.end()) { cout << "Found: " << search->first << " " << search->second << "\n"; OK = false; }
          else map[x] = true;
        }
    }
    
    if (OK) cout << "NO PROBLEM" << endl;
    return 0;
}