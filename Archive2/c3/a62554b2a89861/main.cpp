#include <iostream>
#include <map>

int main () {
    std::map<int,int> m {{1,1},{2,2}};
    for(auto a : m){
        m.erase(a.first);
    }
}
