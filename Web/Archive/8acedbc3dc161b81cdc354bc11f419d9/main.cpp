#include <iostream>
 
typedef unsigned char byte;
typedef char int8;
typedef unsigned char uint8;
typedef short int16;
typedef unsigned short uint16;
typedef int int32;
typedef unsigned int uint32;
typedef long long int64;
typedef unsigned long long uint64;
typedef float single;
 
template < byte b0, byte b1, byte b2, byte b3, byte b4 = b0 + 4, byte b5 = b1 + 4, byte b6 = b2 + 4, byte b7 = b3 + 4 >
struct BaseByteOrder {
        const static byte Positions[8];
        
        static int8 Int8 ( int8 value ) {
                return Value( value );
        }
 
        static int16 Int16 ( int16 value ) {
                return Value( value );
        }
 
        static int32 Int32 ( int32 value ) {
                return Value( value );
        }
 
        static int64 Int64 ( int64 value ) {
                return Value( value );
        }
 
        static uint8 UInt8 ( uint8 value ) {
                return Value( value );
        }
 
        static uint16 UInt16 ( uint16 value ) {
                return Value( value );
        }
 
        static uint32 UInt32 ( uint32 value ) {
                return Value( value );
        }
 
        static uint64 UInt64 ( uint64 value ) {
                return Value( value );
        }
 
        static single Single ( single value ) {
                return Value( value );
        }
 
        static double Double ( double value ) {
                return Value( value );
        }
 
        template <typename T>
        static T Value ( T value ) {
                T out = 0;
                byte* b = (byte*)&value;
                byte* bout = (byte*)&out;
                for ( size_t p = 0; p < sizeof( value ); ++p ) {
                        bout[p] = b[ Positions[p] ];
                }
                return out;
        }
 
};
 
template < byte b0, byte b1, byte b2, byte b3, byte b4, byte b5, byte b6, byte b7>
const byte BaseByteOrder<b0, b1, b2, b3, b4, b5, b6, b7>::Positions[8] = { b0, b1, b2, b3, b4, b5, b6, b7 };
 
template < byte b0, byte b1, byte b2, byte b3, byte b4 = b0 + 4, byte b5 = b1 + 4, byte b6 = b2 + 4, byte b7 = b3 + 4 >
struct ByteOrder;
 
template <int16 order>
struct ByteOrder<order, order, order, order, order, order, order, order>
: public BaseByteOrder< (order & 0xF), ((order & 0xF0) >> 4), ((order & 0xF00) >> 8), ((order & 0xF000) >> 12) > {
 
};
 
template <int32 order>
struct ByteOrder<order, order, order, order, order, order, order, order>
: public BaseByteOrder< (order & 0xF), ((order & 0xF0) >> 4), ((order & 0xF00) >> 8), ((order & 0xF000) >> 12), ((order & 0xF0000) >> 16), ((order & 0xF00000) >> 20), ((order & 0xF000000) >> 24), ((order & 0xF0000000) >> 28) > {
 
};
 
int main (int argc, char* argv[]) {
    
    std::cout << std::hex;
    std::cout << "Argc before: " << argc << std::endl;
    std::cout << "Argc with 0x321: " << ByteOrder<(int16)0x3210>::UInt64( argc ) << std::endl;
    std::cout << "Argc with 0x32107654: " << ByteOrder<(int32)0x32107654>::UInt64( argc ) << std::endl;
    std::cout << "Argc with 0x76543210: " << ByteOrder<(int32)0x76543210>::UInt64( argc ) << std::endl;
    
}