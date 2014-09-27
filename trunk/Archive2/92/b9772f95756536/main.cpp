#include <iostream>
#include <bitset>
#include <new>

struct construct_test
{
    using bitset_type = std::bitset<5> ;

    construct_test()
    {
        std::cout << "in construct_test::constructor: about to construct bitset\n" ;
        new(&c) bitset_type( "10101" ) ; // construct with placement new
        std::cout << "constructed bitset: bitset == " << bitset << '\n' ;
    }

    construct_test( const construct_test& that ) : bitset(that.bitset) {}
    construct_test( construct_test&& that ) noexcept : bitset( std::move(that.bitset) ) {}
    construct_test& operator= ( const construct_test& that ) { bitset = that.bitset ; return *this ; }
    construct_test& operator= ( construct_test&& that ) noexcept { bitset = std::move(that.bitset) ; return *this ; }

    ~construct_test()
    {
        std::cout << "in construct_test::destructor: about to destroy bitset\n"   ;
        bitset.~bitset_type() ; // destroy with explicit call of destructor
        std::cout << "destroyed bitset\n" ;
    }

    private:
        union
        {
            char c ;
            bitset_type bitset ;
        };
};

int main()
{
    construct_test ct ;
}
