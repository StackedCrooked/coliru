#include <iostream>
#include <sstream>
#include <unordered_map>
#include <string>
 
using namespace std ;
 
std::unordered_map<std::string,std::string> mymap;
std::unordered_multimap<std::string,std::string> mymultimap;
void DoAddItem() ;
int main ()
{
    DoAddItem() ;
 
    std::cout << "mymap contains:";
    for ( auto it = mymap.begin(); it != mymap.end(); ++it )
        std::cout << " " << it->first << ":" << it->second;
    std::cout << std::endl;
 
    std::cout << "============================================" << std::endl ;
    std::cout << "mymultimap contains:";
    for ( auto it2 = mymultimap.begin(); it2 != mymultimap.end(); ++it2 )
        std::cout << " " << it2->first << ":" << it2->second;
    std::cout << std::endl;
    return 0;
} 
 
void  DoAddItem() 
{
    std::pair<std::string,std::string> mypair[100]; 
    int idx ;
    std::string s1  ;
    std::string s2  ;
    for(idx=0;idx<10;idx++)
    {
        s1 = string("key") + to_string(idx) ;
        s2 = string("val") + to_string(idx) ;
        mypair[idx] = {s1,s2} ;
        mymap.insert(mypair[idx]) ;
        mymultimap.insert(mypair[idx]) ;
    }//for 
    return ; 
}