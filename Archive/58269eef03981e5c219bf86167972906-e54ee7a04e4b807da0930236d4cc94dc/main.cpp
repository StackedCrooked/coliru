enum MyEnum : unsigned char
{
    i ,j, k, w
};

struct MyStruct
 {
     signed get_mXa() const {return bits&0x7;}
     void set_mXa(signed v) {bits&=0xF8; bits|=(v&0x7);}
     unsigned get_mXb() const {return bits&0x7;}
     void set_mXb(unsigned v) {bits&=0xF8; bits|=(v&0x7);}
     
     signed get_mYa() const {return (bits>>3)&0x7;}
     void set_mYa(signed v) {bits&=0xC7; bits|=((v&0x7)<<3);}
     unsigned get_mYb() const {return (bits>>3)&0x7;}
     void set_mYb(unsigned v) {bits&=0xC7; bits|=((v&0x7)<<3);}
     
     MyEnum get_mEnum() const {return MyEnum((bits>>6)&0x3);}
     void set_mEnum(MyEnum v) {bits&=0x3F; bits|=((v&0x3)<<6);}
     
 private:     
     unsigned char bits;
 };
    
#include <iostream>
int main() {
    std::cout << sizeof(MyStruct);
}