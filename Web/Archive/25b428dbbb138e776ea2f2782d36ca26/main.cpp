#include <iostream>

//#define inlinealways __attribute__((always_inline))
#define inlinealways 

#define enumflagoperators( TEnum ) \
    inlinealways TEnum operator| (const TEnum a, const TEnum b) \
	{return static_cast<TEnum>(static_cast<int>(a) | static_cast<int>(b));} \
	inlinealways TEnum operator& (const TEnum a, const TEnum b) \
	{return static_cast<TEnum>(static_cast<int>(a) & static_cast<int>(b));} \
	inlinealways TEnum operator^ (const TEnum a, const TEnum b) \
	{return static_cast<TEnum>(static_cast<int>(a) ^ static_cast<int>(b));} \
	inlinealways TEnum operator~ (const TEnum a) \
	{return static_cast<TEnum>(~static_cast<int>(a));} \
	inlinealways TEnum& operator|= (TEnum& a, const TEnum b) \
	{a = static_cast<TEnum>(static_cast<int>(a) | static_cast<int>(b)); return a;} \
	inlinealways TEnum& operator&= (TEnum& a, const TEnum b) \
	{a = static_cast<TEnum>(static_cast<int>(a) & static_cast<int>(b)); return a;} \
	inlinealways TEnum& operator^= (TEnum& a, const TEnum b) \
	{a = static_cast<TEnum>(static_cast<int>(a) ^ static_cast<int>(b)); return a;} \
	inlinealways TEnum operator| (const TEnum a, const int b) \
	{return static_cast<TEnum>(static_cast<int>(a) | static_cast<int>(b));} \
	inlinealways TEnum operator& (const TEnum a, const int b) \
	{return static_cast<TEnum>(static_cast<int>(a) & static_cast<int>(b));} \
	inlinealways TEnum operator^ (const TEnum a, const int b) \
	{return static_cast<TEnum>(static_cast<int>(a) ^ static_cast<int>(b));} \
	inlinealways TEnum operator| (const int a, const TEnum b) \
	{return static_cast<TEnum>(static_cast<int>(a) | static_cast<int>(b));} \
	inlinealways TEnum operator& (const int a, const TEnum b) \
	{return static_cast<TEnum>(static_cast<int>(a) & static_cast<int>(b));} \
	inlinealways TEnum operator^ (const int a, const TEnum b) \
	{return static_cast<TEnum>(static_cast<int>(a) ^ static_cast<int>(b));} \
	inlinealways TEnum& operator|= (TEnum& a, const int b) \
	{a = static_cast<TEnum>(static_cast<int>(a) | static_cast<int>(b)); return a;} \
	inlinealways TEnum& operator&= (TEnum& a, const int b) \
	{a = static_cast<TEnum>(static_cast<int>(a) & static_cast<int>(b)); return a;} \
	inlinealways TEnum& operator^= (TEnum& a, const int b) \
	{a = static_cast<TEnum>(static_cast<int>(a) ^ static_cast<int>(b)); return a;} \
    static_assert( true, "Fuck you" )
    
    
enum class FlagsnShit {
    None = 0x00,
    One = 0x01,
    Two = 0x02,
    OneTwo = One | Two,
};

enumflagoperators( FlagsnShit );
    
int main ( int argc, char* argv[] ) {
    
    FlagsnShit flags = FlagsnShit::One | FlagsnShit::Two;
    std::cout << std::hex;
    std::cout << (int)flags << std::endl;
    std::cout << ( flags == FlagsnShit::OneTwo ) << std::endl;
}