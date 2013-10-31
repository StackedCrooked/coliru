#include <iostream>
#include <string>
#include <vector>

namespace barname {
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
}
