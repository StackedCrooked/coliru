#include <iostream>
#include <sstream>
#include <string>
#include <vector>


namespace foo {
    struct myval {unsigned long long val_;}; 
    myval operator ""_val(unsigned long long val) {return myval{val};} 
    unsigned long long operator*(myval val, unsigned long long howmany) 
    {
        std::stringstream s; 
        s << val.val_; 
        std::string result; 
        for (unsigned int i = 0; i < howmany; ++i) {
            result += s.str();
        } 
        unsigned long long final_result; 
        s.clear(); 
        s.str(result); 
        s >> final_result; 
        return final_result;
    }
} 
int main() 
{
    using foo::operator""_val; 
    std::cout << (6_val * 10) << std::endl;
    std::cout << (2_val * 10) << std::endl;
}

