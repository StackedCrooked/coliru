#include <iostream>


#define TRACE std::cout << __PRETTY_FUNCTION__ << std::endl;


namespace array_api
{    
    struct array {};
    
    void print(const array&) { TRACE }
}


namespace list_api
{
    struct list {};    
    
    void print(const list&) { TRACE }
}


namespace api
{
    using array_api::array;
    using list_api::list;
}


int main()
{    
    api::array a;
    print(a);
}
