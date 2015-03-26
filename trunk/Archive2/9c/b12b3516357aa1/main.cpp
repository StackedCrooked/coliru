#include <iostream>
using namespace std;

struct serializator_tag {};
struct special_serializator_tag : serializator_tag {};

template<typename> struct traits;

struct Serializator {};

template<>
struct traits<Serializator>
{
    typedef serializator_tag tag;
};

struct SpecialSerializator {};

template<>
struct traits<SpecialSerializator>
{
    typedef special_serializator_tag tag;
};

/****************************************************************/

template<typename S>
void serialize(S x, serializator_tag)
{
    cout << "Basic Serializator" << endl;
}

template<typename S>
void serialize(S x, special_serializator_tag)
{
    cout << "Special Serializator" << endl;
}

template<typename S>
void serialize(S x)
{
    serialize(x, typename traits<S>::tag());
}

int main()
{
    serialize( Serializator() );
    serialize( SpecialSerializator() );
}

