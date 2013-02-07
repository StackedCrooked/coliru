#include <iostream>

//#define inlinealways __attribute__((always_inline))
#define inlinealways 

#define enummathoperatorsbyusing( TEnum, TOther, TIntegral ) \
    inlinealways TEnum operator+ (const TEnum a, const TOther b) \
	{return static_cast<TEnum>(static_cast<TIntegral>(a) + static_cast<TIntegral>(b));} \
	inlinealways TEnum operator- (const TEnum a, const TOther b) \
	{return static_cast<TEnum>(static_cast<TIntegral>(a) - static_cast<TIntegral>(b));} \
	inlinealways TEnum operator* (const TEnum a, const TOther b) \
	{return static_cast<TEnum>(static_cast<TIntegral>(a) * static_cast<TIntegral>(b));} \
	inlinealways TEnum operator/ (const TEnum a, const TOther b) \
	{return static_cast<TEnum>(static_cast<TIntegral>(a) / static_cast<TIntegral>(b));} \
	static_assert( true, "enummathoperatorswithintegral" )

#define enummathoperatorswith( TEnum, TOther ) enummathoperatorsbyusing( TEnum, TOther, int )
#define enummathoperators( TEnum ) enummathoperatorsbyusing( TEnum, TEnum, int )

#define enumflagoperatorsselfusing( TEnum, TIntegral ) \
	inlinealways TEnum operator| (const TEnum a, const TEnum b) \
	{return static_cast<TEnum>(static_cast<TIntegral>(a) | static_cast<TIntegral>(b));} \
	inlinealways TEnum operator& (const TEnum a, const TEnum b) \
	{return static_cast<TEnum>(static_cast<TIntegral>(a) & static_cast<TIntegral>(b));} \
	inlinealways TEnum operator^ (const TEnum a, const TEnum b) \
	{return static_cast<TEnum>(static_cast<TIntegral>(a) ^ static_cast<TIntegral>(b));} \
	inlinealways TEnum& operator|= (TEnum& a, const TEnum b) \
	{a = static_cast<TEnum>(static_cast<TIntegral>(a) | static_cast<TIntegral>(b)); return a;} \
	inlinealways TEnum& operator&= (TEnum& a, const TEnum b) \
	{a = static_cast<TEnum>(static_cast<TIntegral>(a) & static_cast<TIntegral>(b)); return a;} \
	inlinealways TEnum& operator^= (TEnum& a, const TEnum b) \
	{a = static_cast<TEnum>(static_cast<TIntegral>(a) ^ static_cast<TIntegral>(b)); return a;} \
	inlinealways TEnum operator~ (const TEnum a) \
	{return static_cast<TEnum>( ~static_cast<TIntegral>(a) );} \
	static_assert( true, "enumflagoperatorsself" )

#define enumflagoperatorsusing( TEnum, TIntegral ) \
	inlinealways TEnum operator| (const TEnum a, const TIntegral b) \
	{return static_cast<TEnum>(static_cast<TIntegral>(a) | static_cast<TIntegral>(b));} \
	inlinealways TEnum operator& (const TEnum a, const TIntegral b) \
	{return static_cast<TEnum>(static_cast<TIntegral>(a) & static_cast<TIntegral>(b));} \
	inlinealways TEnum operator^ (const TEnum a, const TIntegral b) \
	{return static_cast<TEnum>(static_cast<TIntegral>(a) ^ static_cast<TIntegral>(b));} \
	inlinealways TEnum operator| (const TIntegral a, const TEnum b) \
	{return static_cast<TEnum>(static_cast<TIntegral>(a) | static_cast<TIntegral>(b));} \
	inlinealways TEnum operator& (const TIntegral a, const TEnum b) \
	{return static_cast<TEnum>(static_cast<TIntegral>(a) & static_cast<TIntegral>(b));} \
	inlinealways TEnum operator^ (const TIntegral a, const TEnum b) \
	{return static_cast<TEnum>(static_cast<TIntegral>(a) ^ static_cast<TIntegral>(b));} \
	inlinealways TEnum& operator|= (TEnum& a, const TIntegral b) \
	{a = static_cast<TEnum>(static_cast<TIntegral>(a) | static_cast<TIntegral>(b)); return a;} \
	inlinealways TEnum& operator&= (TEnum& a, const TIntegral b) \
	{a = static_cast<TEnum>(static_cast<TIntegral>(a) & static_cast<TIntegral>(b)); return a;} \
	inlinealways TEnum& operator^= (TEnum& a, const TIntegral b) \
	{a = static_cast<TEnum>(static_cast<TIntegral>(a) ^ static_cast<TIntegral>(b)); return a;} \
	static_assert( true, "enumflagoperatorswith" )

#define enumflagoperatorswith( TEnum, TIntegral ) enumflagoperatorsselfusing( TEnum, TIntegral ); enumflagoperatorsusing( TEnum, TIntegral )
#define enumflagoperatorsself( TEnum ) enumflagoperatorsselfusing( TEnum, int )
#define enumflagoperators( TEnum ) enumflagoperatorswith( TEnum, int )
    
    
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