#include <iostream>
#include <map>
#include <string>

int main()
{
    std::cout << "\nkeys are in increasing order: \n";
    std::map<int, std::string> m1;
    m1[5] = "first insertion but higher key";
    m1[1] = "second insertion but lower key";
    for(auto const & item : m1) 
       std::cout << "{" << item.first  <<"," << item.second << "}\n";
       
    std::cout << "\nkeys are in decreasing order: \n";   
    std::map<int, std::string, std::greater<int> > m2;
    m2[1] = "first insertion but lower key";
    m2[2] = "second insertion but higher key";
    for(auto const & item : m2) 
       std::cout << "{" << item.first  <<"," << item.second << "}\n";
}