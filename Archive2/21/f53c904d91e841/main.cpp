#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

class Link
{
    public:
    Link():m_LinkID(0){}
    
    Link(int id):m_LinkID(id){}
    
    void SetLinkFlag(bool i_flag){}   
    
    unsigned long GetID()const{return m_LinkID;}
    
    private:
    int m_LinkID;    
};

std::ostream& operator<<(std::ostream& os, const std::vector<Link>& vec)
{
    for (auto& el : vec)    
        os << el.GetID() << ' ';
    
    return os;
}

int main()
{
   // std::vector<std::string> words = { "Hello", "from", "GCC", __VERSION__, "!"   };    
   // std::cout << words << std::endl;
    
    std::vector<Link> vecLinks={2,3,4};    
    std::cout<<vecLinks<<std::endl;
    
    vecLinks.emplace_back(5);
     std::cout<<vecLinks<<std::endl;
    
    
    std::for_each(vecLinks.begin(),vecLinks.end(),[](Link& io_Link){io_Link.SetLinkFlag(true);});   
    
}
