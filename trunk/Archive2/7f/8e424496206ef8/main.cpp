#include <iostream>
#include <memory>
#include <vector>

void dump( std::unique_ptr<int>& p, const char* name )
{
    std::cout <<'\'' << name << "' std::unique_ptr<int> at address: "
               << std::addressof(p) << "\n\tpoints to int at address: " << p.get() ;

    if(p) std::cout << " which has the value: " << *p  << "\n\n" ;
    else std::cout << " (nullptr)\n\n" ;
}

int main()
{
     std::vector< std::unique_ptr<int> > vec ;

     std::unique_ptr<int> temp( new int(999) ) ;
     dump( temp, "temp" ) ;

     // move the unique_ptr to the vector
     vec.push_back( std::move(temp) ) ;
     std::cout << "temp has been moved to vec[0]\n\n" ;

     // temp and vec[0] are two different unique_ptr<int> instances.
     dump( temp, "temp" ) ; // temp is now a nullptr
     dump( vec[0], "vec[0]" ) ; // vec[0] points to the integer

     // conclusion: modifying temp will not modify vec[0]
     std::cout << "modify temp\n\n" ;
     temp.reset( new int (-77) ) ;
     dump( temp, "temp" ) ; // temp now points to int -77
     dump( vec[0], "vec[0]" ) ; // vec[0] remains unchanged
}
