/*
 Demangling C++ symbol short demo.
 Author: Prashant Srivastava
*/

#include <map>
#include <string>
#include <algorithm>
#include <vector>


std::map<char, int> foo( const std::string& str, int& x )
{
    std::map<char, int> m ;
    for_each( str.begin(), str.end(), 
                           [&x,&m](const char p)
                           {
                               
                               m[p] = ++x;
                           }
            );
    return m;
}
                    
    
int main()
{
   std::vector <int> v;
   v.push_back(4) ;
}