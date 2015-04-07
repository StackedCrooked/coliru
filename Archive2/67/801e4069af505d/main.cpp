#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

std::string fSig(const std::string& sig)
{
    if (sig.back() != '>')
        return sig; 
    
    //unsigned int i = 1;
    auto it = sig.end() - 2;
    
    for(unsigned i = 1; i != 0; --it)
    {
        if(*it == '<')
        {
            --i;
            std::cout << "sub" << std::endl;
        }
        else if(*it == '>')
        {
            ++i;
            std::cout << "add" << std::endl;
        }
        else
        {
            std::cout << "boo" << std::endl;
        }
    }
/*    
    while(i != 0)
    {
        std::cout << "---> " << *it << std::endl;
        if (*it == '<')
            --i;
        if (*it == '>')
            ++i;
        --it;
    }
*/  
        
    return "hello";
}

int main()
{
    std::string sig = "Jungle::Tiger<std::vector<std::string> >";
    

    std::cout << fSig(sig) << std::endl;
}
