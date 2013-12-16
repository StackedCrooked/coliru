#include <iostream>
#include <memory>
#include <array>

int main()
{
    struct block { ~block() { std::cout << "destructor: " << this << '\n' ; } };

    std::array< std::unique_ptr<block>, 5 > blocks ;

    const auto& print = [&blocks]
    {   for( auto& p : blocks ) std::cout << p.get() << ' ' ;
        std::cout << "\n\n" ;
    };

    print() ;

    blocks[1] = std::unique_ptr<block>( new block ) ;
    blocks[2] = std::unique_ptr<block>( new block ) ;
    blocks[4] = std::unique_ptr<block>( new block ) ;
    print() ;

    blocks[2] = 0 ; // calls deleter on blocks[2]
    print() ;

    blocks = {0} ; // calls deleter on all non-null pointers
    print() ;
}
