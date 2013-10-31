#include <iostream>
#include <string>
#include <vector>

namespace barname 
{
    class CFoo
    {
    public:
        CFoo();
        ~CFoo();
    
        static void fooMethod();
    };
    
    inline CFoo::CFoo()
    {
    }
    
    inline CFoo::~CFoo()
    {
        fooMethod();
    }
    
    void CFoo::fooMethod()
    {
        std::cout << "in fooMethod" << std::endl;
    }
}


int main()
{
    barname::CFoo *f = new barname::CFoo();
    delete f;
}
