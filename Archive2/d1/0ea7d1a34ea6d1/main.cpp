#include <memory>
#include <iostream>
#include <map>
 
struct Foo {
    Foo() { std::cout << "Foo...\n"; }
    ~Foo() { std::cout << "~Foo...\n"; }
};
 
struct D { 
    void operator()(Foo* p) const {
        std::cout << "Call delete for Foo object...\n";
        delete p;
    }
};

struct mapper
{
    std::map< std::string, std::shared_ptr< const Foo > > map_;
    void add( const std::string& key,  const Foo* foo )
    {
        map_[ key ] = std::shared_ptr<const Foo>(foo);
    }
    void add( const std::string& key, const std::shared_ptr< const Foo >& foo )
    {
        map_[ key ] = foo;
    }
};
 
int main()
{
    {
        std::cout << "constructor with no managed object\n";
        std::shared_ptr<Foo> sh1;
    }
 
    {
        std::cout << "constructor with object\n";
        std::shared_ptr<Foo> sh2(new Foo);
        std::shared_ptr<Foo> sh3(sh2);
        std::cout << sh2.use_count() << '\n';
        std::cout << sh3.use_count() << '\n';
    }
 
    {
        std::cout << "constructor with object and deleter\n";
        std::shared_ptr<Foo> sh4(new Foo, D());
    }
    {
        mapper mapr;
        mapr.add( "test", new Foo );
        std::cout << "added test\n";
    }
    std::cout << "finished\n";
    
}