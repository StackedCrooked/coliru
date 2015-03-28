#include <iostream>

unsigned int bitFlags()
{
unsigned char option1 = 0x01; // hex for 0000 0001
unsigned char option2 = 0x02; // hex for 0000 0010
unsigned char option3 = 0x04; // hex for 0000 0100
//unsigned char option4 = 0x08; // hex for 0000 1000
//unsigned char option5 = 0x10; // hex for 0001 0000
//unsigned char option6 = 0x20; // hex for 0010 0000
//unsigned char option7 = 0x40; // hex for 0100 0000
unsigned char option8 = 0x80; // hex for 1000 0000

unsigned char myflags; // byte-size value to hold some combination of the above 8 options

myflags |= option1|option2|option3;

if (myflags&option8)
    return 1;
else
    return 0;
}

int main()
{
   std::cout << bitFlags() << "\n";
    return 0;
}