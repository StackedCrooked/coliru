#include <iostream>
#include <bitset>
#include <string>

int main()
{
    std::bitset<21> trigger( "10110111000111001" ) ;
    std::cout << trigger << '\n' ; // 000010110111000111001

    trigger[5] = false ;
    trigger[10] = true ;
    trigger[20].flip() ;
    std::cout << trigger << '\n' ; // 100010110111000011001

    std::cout << std::hex << std::showbase << trigger.to_ulong() << '\n' ; // 0x116e19
    trigger = 0xabcdef ;
    std::cout << trigger << '\n' // 010111100110111101111
              << trigger.to_ulong() << std::dec << '\n' ; // 0xbcdef

    std::string flags = "flags: " + trigger.to_string() ;
    std::cout << flags << '\n' ; // flags: 010111100110111101111

    // some of the bits are set
    if( trigger.any() ) std::cout << "some of the bits are set\n" ;
    else std::cout << "no bit is set\n" ;

    // not all the bits are set
    if( trigger.all() ) std::cout << "all the bits are set\n" ;
    else std::cout << "not all the bits are set\n" ;

    // 15 of 21 bits are set
    std::cout << std::dec << trigger.count() << " of " << trigger.size() << " bits are set\n" ;

    trigger = 0 ;
    // no bit is set
    if( trigger.any() ) std::cout << "some of the bits are set\n" ;
    else std::cout << "no bit is set\n" ;

    trigger = ~trigger ;
    // all the bits are set
    if( trigger.all() ) std::cout << "all the bits are set\n" ;
    else std::cout << "not all the bits are set\n" ;
}
