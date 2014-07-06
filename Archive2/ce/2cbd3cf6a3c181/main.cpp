#include <iostream>
#include <map>
#include <memory>

class test_class{
public:
    std::map <int, int> my_map;
};

int main( )
{
    std::shared_ptr< test_class > test( new test_class );
    
    test->my_map[5] = 10 ;
    test->my_map[6] = 11 ;
    test->my_map[7] = 12 ;
    test->my_map[8] = 13 ;
    
    for(const auto& x: test->my_map )
    
      std::cout<<x.first << ":" << x.second << std::endl ;
    
}