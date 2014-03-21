#include <iostream>


template<typename T>
void print()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}


template<int N>
struct Traits;


template<>
struct Traits<0>
{
    typedef void type;
};


template<int N>
struct Traits : Traits<N - 1>
{
};


#define REGISTER_TYPE(Type) \
    struct Type { typedef typename Traits<__LINE__ - 1>::type previous_type; }; \
    template<> struct Traits<__LINE__> { typedef Type type; };



REGISTER_TYPE(Spades)

REGISTER_TYPE(Hearts)

REGISTER_TYPE(Diamonds)

REGISTER_TYPE(Clubs)


static_assert(std::is_same<Spades::previous_type,   void>::value, "");
static_assert(std::is_same<Hearts::previous_type,   Spades>::value, "");
static_assert(std::is_same<Diamonds::previous_type, Hearts>::value, "");
static_assert(std::is_same<Clubs::previous_type,    Diamonds>::value, "");
    
    
int main()
{
}