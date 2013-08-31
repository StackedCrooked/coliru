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
	{a = static_cast<TEnum>(static_cast<int>(a) ^ static_cast<int>(b)); return a;}
    
int main ( int argc, char* argv[] ) {
    
}