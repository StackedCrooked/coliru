#include <iostream>
#include <functional>
#include <queue>
#include <future>
#include <type_traits>
#include <algorithm>
#include <ostream>
#include <sstream>      // std::ostringstream

class A
{
    public:
        A() { test = -2.f; }
        ~A() = default;
        
        std::ostream& serialize(std::ostream& out)
        {
            return out << test;
            
        };
        
        std::istream& unserialize(std::istream& in)
        {
            return in >> test;
        };
        
    private:
        float test;
};

class TMP
{
    public:
        TMP() { test = 3; }
        ~TMP() = default;
        
        std::ostream& serialize(std::ostream& out)
        {
            out << test;
            
            test = 5;
            
            return a.serialize(out);
            
        };
        
        std::istream& unserialize(std::istream& in)
        {
            in >> test;
            
            std::cout << "HERE: " << test << std::endl;
            
            return a.unserialize(in);
            
        };
    
    private:
        A a;
        int test;
};

int main()
{
    TMP tmp;

    std::stringstream saveFile;

    std::cout << tmp.serialize(saveFile);
    
    tmp.unserialize(saveFile);
    
    return 0;
}