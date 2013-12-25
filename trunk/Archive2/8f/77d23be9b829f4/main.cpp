

#include <string>
#include <iostream>
#include <chrono>
#include <ctime>
#include <functional>
#include <vector>

struct S
{
    void setNameByValue( std::string value ) // sometimes creates copy (for temporaries or explicit std::move call - no copy)
    {
        name_ = std::move( value );
    }
    
    void setNameByCRef( const std::string& value )
    {
        name_ = value; // always copy
    }

    std::string name_;
};

void trackTime2(const std::string& message)
{
    auto startTime = std::chrono::high_resolution_clock::now();
    std::vector<std::string> v;
    v.reserve(25000000);
    for (int i = 0; i < 25000000; ++i)
    {
        v.emplace_back("hello");
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    std::cout << message << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << "ms" << std::endl;
}
template< typename FuncF >
void trackTime(const std::string& message, FuncF f)
{
    auto startTime = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 2000000; ++i)
    {
        f();
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    std::cout << message << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << "ms" << std::endl;
}
int main()
{
    S s;
    trackTime2("vector push_back: ");
    
    trackTime("Temporary by Value: ", [&s]{ s.setNameByValue("foooooooooooooooooooooooooooooooooooooooooooo!"); });
    trackTime("Temporary by CRef: ", [&s]{ s.setNameByCRef("foooooooooooooooooooooooooooooooooooooooooooo!"); });
    
    trackTime("Non temporary by Value: ", [&s]{ 
        std::string data("foooooooooooooooooooooooooooooooooooooooooooo");
        s.setNameByValue(data); });
        
    trackTime("Non temporary by CRef: ", [&s]{ 
        std::string data("foooooooooooooooooooooooooooooooooooooooooooo");
        s.setNameByCRef(data); });
    
    
}