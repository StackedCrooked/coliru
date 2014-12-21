#include <iostream>
#include <utility>
#include <string>
 
#include <map>
#include <vector>

class Foo
{
public:
    Foo ( int _a, const char* name ) : a ( _a )
    {
        std::cout << "constructor" << a << " name " << name << std::endl;
    }
    
    Foo ( const Foo&other ) : a ( other.a )
    {
        std::cout << "copy " << other.a << std::endl;
    }
    
    Foo ( Foo&& other ) : a ( other.a )
    { 
        std::cout <<"move" << other.a << std::endl;      
    }  
    
    Foo& operator= (Foo&& other )
    {
        if ( this == &other )
            return *this;
        std::cout << "move=" << other.a << std::endl;
        a = std::move(other.a);
        return *this;
    }
    
private:
    int a;
};
int main()
{
    std::vector <Foo> vec;
    Foo alon (1,"vec1"); // Constuctor
    
    vec.push_back ( alon ); // Copy const
    vec.push_back ( Foo(2,"vec2")); // Constuctor + move
    vec.emplace_back ( 3, "vec3"); // only constructor
}