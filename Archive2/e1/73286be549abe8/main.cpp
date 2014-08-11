#include <iostream>
#include <bitset>
#include <string>

int main()
{
    std::bitset<21> actions( "10110111000111001" ) ;
    std::cout << actions << '\n' ; // 000010110111000111001

    actions[5] = false ;
    actions[10] = true ;
    actions[20].flip() ;
    std::cout << actions << '\n' ; // 100010110111000011001

    std::cout << std::hex << std::showbase << actions.to_ulong() << '\n' ; // 0x116e19
    actions = 0xabcdef ;
    std::cout << actions << '\n' // 010111100110111101111
              << actions.to_ulong() << std::dec << '\n' ; // 0xbcdef

    std::string flags = "flags: " + actions.to_string() ;
    std::cout << flags << '\n' ; // flags: 010111100110111101111

    // some of the bits are set
    if( actions.any() ) std::cout << "some of the bits are set\n" ;
    else std::cout << "no bit is set\n" ;

    // not all the bits are set
    if( actions.all() ) std::cout << "all the bits are set\n" ;
    else std::cout << "not all the bits are set\n" ;

    // 15 of 21 bits are set
    std::cout << std::dec << actions.count() << " of " << actions.size() << " bits are set\n" ;

    actions = 0 ;
    // no bit is set
    if( actions.any() ) std::cout << "some of the bits are set\n" ;
    else std::cout << "no bit is set\n" ;

    actions = ~actions ;
    // all the bits are set
    if( actions.all() ) std::cout << "all the bits are set\n" ;
    else std::cout << "not all the bits are set\n" ;
}
