#include <iostream>
#include <utility>
#include <string>
 
#include <map>
#include <vector>

class Foo
{
public:
    Foo ( const int _a, const std::string _dummy ) : a ( _a ), dummy ( _dummy )
    { std::cout << "const " << a << std::endl; }
    
    Foo ( const Foo& other ) : Foo ( other.a, other.dummy )
    { std::cout << "copy " << other.a << std::endl; }
    
    Foo ( const Foo&& other )
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
    
    std::cout << "Vector:" << std::endl;
    
    Foo bar (1, "1"); /* constuctor only */
    vec.push_back ( bar ); /* copy consutrctor */
    vec.push_back (Foo(2,"2")); /* consturctor, move constructor (rvalue) */
    vec.emplace_back ( 3,"3" ); /* only constructor */
    
    std::cout << std::endl << "Map:" << std::endl;
    
    std::map <int,Foo> map;
    map.insert ( std::make_pair<int,Foo> (1, Foo(1,"Foo1")) );
    map.emplace ( std::piecewise_construct, std::make_tuple(2), std::make_tuple (2, "Foo2") );
}