#include <string>

std::string& foo( std::string& str ) { return str ; }

std::string bar( std::string& str ) { return str ; }

int main()
{
    std::string s ;
    
    std::string& fine = foo(s) ; // fine, reference to non-temporary object
    
    const std::string& also_fine = foo(s) ; // fine, reference to const extends the life of the temporary object

    std::string& not_fine = bar(s) ; // *** error *** reference to non-const can't bind to a temporary object 
}