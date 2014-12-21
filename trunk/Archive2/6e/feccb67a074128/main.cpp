#include <iostream>
#include <utility>
#include <string>
 
#include <map>
#include <vector>

class Foo
{
public:
    Foo ( int _a, std::string _dummy ) : a ( _a ), dummy ( _dummy )
    { std::cout << "const " << a << std::endl; }
    
    Foo ( const Foo& other ) : Foo ( other.a, other.dummy )
    { std::cout << "copy " << other.a << std::endl; }
    
    Foo ( Foo&& other )
    { 
        a = std::move ( other.a );
        dummy = std::move ( other.dummy );
        std::cout << "move " << other.a << std::endl;        
    }
    
    Foo& operator= ( const Foo& other )
    {
        if ( this == &other) return *this;
        a = other.a;
        dummy = other.dummy;
        std::cout << "copy= " << other.a << std::endl;
        return *this;
    }
    
    Foo& operator= (const Foo&& other )
    {
        if ( this ==&other ) return *this;
        a = std::move(other.a);
        dummy = std::move(other.dummy);
        std::cout << "move= " << other.a << std::endl;
        return *this;
    }
private:
    int a;
    std::string dummy;
};

int main()
{
    std::vector <Foo> vec;
    
    Foo bar (1, "1"); /* constuctor only */
    vec.push_back ( bar ); /* copy consutrctor */
    vec.push_back (Foo(2,"2")); /* consturctor, move constructor (rvalue) */
    vec.emplace_back ( 3,"3" ); /* only constructor */
}