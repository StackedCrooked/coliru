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
    
    std::cout << "Foo():\n";
    Foo bar (1, "1"); /* constuctor only */
    std::cout << "push_back bar:\n";
    vec.push_back ( bar ); /* copy consutrctor */
    std::cout << "push_back Foo():\n";
    vec.push_back (Foo(2,"2")); /* consturctor, move constructor (rvalue) */
    std::cout << "emplace_back:\n";
    vec.emplace_back ( 3,"3" ); /* only constructor */
    
    std::cout << std::endl << "Map:" << std::endl;
    
    std::map <int,Foo> map;
    std::cout << "insert:\n";
    map.insert ( std::make_pair<int,Foo> (1, Foo(1,"Foo1")) );
    std::cout << "emplace1:\n";
    map.emplace ( 2, Foo (2, "Foo2"));
    std::cout << "emplace2:\n";
    map.emplace ( std::piecewise_construct, std::make_tuple(3), std::make_tuple (3, "Foo3") );
}