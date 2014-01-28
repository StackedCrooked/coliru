#include <iostream>
#include <map>

// constructing maps
std::map<char,int> first;

int main ()
{
    first['a']=10;
    first['b']=30;
    first['c']=50;
    first['d']=70;
    
    std::map<char,int> second (first.begin(),first.end());

    std::map<char,int> third (second);

    std::map<char,int>::iterator i;
    char c;
    for(i=first.begin(),c='a';i!=first.end();i++,c++)
        std::cout<<first[c]<<std::endl;
    return 0;
}