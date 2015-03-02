#include <cstdio>
#include <string>

int main()
{
    std::string s = "Potatona_15.minion";
    
    int i = 0;
    sscanf(s.c_str(), "Potatona_%d.minion", &i);
    printf("%d", i);
    
    return 0;
}