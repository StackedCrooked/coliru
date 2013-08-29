#include <type_traits>
#include <vector>
#include <iostream>

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

#define enummathoperatorswith( TEnum, TOther ) enummathoperatorsbyusing( TEnum, TOther, std::underlying_type<TEnum>::type )
#define enummathoperators( TEnum ) enummathoperatorsbyusing( TEnum, TEnum, std::underlying_type<TEnum>::type )

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
	static_assert( true, "enumflagoperatorsselfusing" )

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
	static_assert( true, "enumflagoperatorsusing" )

#define enumflagoperatorswith( TEnum, TIntegral ) enumflagoperatorsselfusing( TEnum, TIntegral ); enumflagoperatorsusing( TEnum, TIntegral )
#define enumflagoperatorsself( TEnum ) enumflagoperatorsselfusing( TEnum, std::underlying_type<TEnum>::type )
#define enumflagoperators( TEnum ) enumflagoperatorswith( TEnum, std::underlying_type<TEnum>::type )

template <typename TFlag> 
inlinealways bool HasFlags( TFlag value, TFlag flags ) {
	return (value & flags) == flags;
}

template <typename TFlag> 
inlinealways bool HasAnyFlag( TFlag value, TFlag flags ) {
	return (value & flags) != static_cast<TFlag>( 0 );
}

template <typename TFlag> 
inlinealways bool DoesNotHaveFlag( TFlag value, TFlag flags ) {
	return (value & flags) == static_cast<TFlag>( 0 );
}

enum class BitWise {
    None = 0,
    Flag1 = 0x01,
    Flag2 = 0x02,
    Flag4 = 0x08,
};

enumflagoperators( BitWise );

int main()
{
    BitWise bitwise = BitWise::None;
    BitWise orme = bitwise | BitWise::Flag2;
    
    std::cout << static_cast<int>( orme ) << std::endl;
}