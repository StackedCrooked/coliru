#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define COPIER(ovec,ivec,type,field,value)                \
        std::copy_if(ovec.begin(),ovec.end(),ivec.begin(),\
        [&](type const& v)                                \
        {                                                 \
            return v.field == value;                      \
        })
        
struct s
{
    std::string one;
    std::string two;
    int         int_;
    
    s(std::string o, std::string t, int i)
    : one(o),two(t),int_(i)
    {}
    s(){}

};

std::ostream& operator << (std::ostream& os, s const& v)
{
    os << v.one << " " << v.two << " " << v.int_;
    return os;
}

int main()
{
    std::vector<s> vec = 
            { 
              s("smoke","lock",10), 
              s("smoke","lose",5),
              s("s","by_value",11),
              s("s3","by_value",12)
            };
    
    std::vector<s> on_char, by_value;
    on_char.resize(2); by_value.resize(2);
    COPIER(vec,on_char,s,one,"smoke");
    std::string str = "by_value";
    COPIER(vec,by_value,s,two,str);
    
    std::cout << "by_value :\n";
    for (auto& a : by_value)
        std::cout << a << "\n";
    
    std::cout << "char :\n";
    for (auto& a : on_char)
        std::cout << a << "\n";
    
}
