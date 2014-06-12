

#include <string>
#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <functional>

struct S
{
    void setNameByValue( std::vector< int > value ) // sometimes creates copy (for temporaries or explicit std::move call - no copy)
    {
        name_ = std::move( value );
    }
    
    void setNameByCRef( const std::vector< int >& value )
    {
        name_ = value; // always copy
    }

    std::vector< int > name_;
};

template< typename FuncF >
void trackTime(const std::string& message, FuncF f)
{
    auto startTime = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 600000; ++i)
    {
        f();
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    std::cout << message << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << "ms" << std::endl;
}
int main()
{
    S s;
    trackTime("create vector: ", [&s]{ 
        std::vector< int > data(10000, 0xff);
        data[0] = 1;
    });
    trackTime("Temporary by Value: ", [&s]{
        s.setNameByValue(std::vector< int >(10000, 0xff)); 
    });
    
    trackTime("Temporary by CRef: ", [&s]{
        s.setNameByCRef(std::vector< int >(10000, 0xff)); 
    });
    std::vector< int > data(10000, 0xff);

    trackTime("Non temporary by CRef: ", [&s, &data]{ 
        s.setNameByCRef(data); });

    trackTime("Non temporary by Value: ", [&s, &data]{ 
        s.setNameByValue(data); 
        });
        

    
    
}