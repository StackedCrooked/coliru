#include <algorithm>
#include <string>
#include <iostream>
 
int main()
{
    #include <algorithm>
k=3
s="aba"
    for(int j = 1; j < s.size(); ++j) 
    {
        std::swap(s[k % (j + 1)], s[j]); 
        k = k / (j + 1);
    }

}