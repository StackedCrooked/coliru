#include <iostream>
#include <string>
#include <map>

class P{};
class D0: public P{};
class D1: public P{};

int main()
{
    std::map<int, P*> p_map;
    
    p_map.add(0, new P);
}
