

#include <iostream>
#include <sstream> //for std::stringstream 
#include <string>  //for std::string


struct X
{
    std::string name() const
    {
        //const void * address = static_cast<const void*>(this);
        std::stringstream ss;
        //ss << address;  
        ss << this;
        return ss.str(); 
    }
    
    friend std::ostream& operator<<(std::ostream & out, X const * const x)
    {
        return out << "HAHA";
    }
};

int main()
{
    std::cout << X().name() << std::endl;
}
