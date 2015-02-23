#include <iostream>
#include <vector>
#include <string>

class Example
{
     private:
            std::vector<std::string> names ;
     public:
            void set_all_names( std::vector<std::string> n );
            void add_one_name( std::string name );
            std::vector<std::string> get_all_names() const ;
};

void Example::set_all_names( std::vector<std::string> n ) { names = n ; }

void Example::add_one_name( std::string name ) { names.push_back(name) ; }

std::vector<std::string> Example::get_all_names() const { return names ; }

int main()
{
    Example e ;
    e.set_all_names( { "peter", "paul", "mary" } ) ;
    e.add_one_name( "john doe " ) ;

    const std::vector<std::string> vec= e.get_all_names() ;
    for( std::string n : vec ) std::cout << n << '\n' ;
}
