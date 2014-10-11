#include <vector>
#include <type_traits>
#include <iostream>

int main()
{
    std::vector<int> vec ;
    const auto& const_vec = vec ;
    
    auto iter = vec.begin() ;
    static_assert( std::is_same< decltype(iter), std::vector<int>::iterator >::value, "must be std::vector<int>::iterator" ) ;

    auto citer = const_vec.begin() ;
    static_assert( std::is_same< decltype(citer), std::vector<int>::const_iterator >::value, "must be std::vector<int>::const_iterator" ) ;
    
    static_assert( std::is_convertible< std::vector<int>::iterator, std::vector<int>::const_iterator >::value, 
                                        "there must be an implicit converstion from iterator to const_iterator" ) ;
                                        
    static_assert( !std::is_convertible< std::vector<int>::const_iterator, std::vector<int>::iterator >::value, 
                                        "there can't be an implicit converstion from const_iterator to iterator" ) ;
                                        
    std::cout << "ok.\n" ;                                    
}
