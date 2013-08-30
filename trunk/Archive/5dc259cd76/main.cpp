#include <cassert>
#include <iostream>

struct NullType;

template <
    typename T1 = NullType,
    typename T2 = NullType,
    typename T3 = NullType >
struct TypeList
{
    typedef T1 Head;
    typedef TypeList< T2, T3 > Tail;
};

template <>
struct TypeList<>
{
};

template <int N, typename LIST>
struct NthType
{
    typedef typename NthType< N - 1, typename LIST::Tail >::Type Type;
};

template <typename LIST>
struct NthType< 0, LIST >
{
    typedef typename LIST::Head Type;
};

template <typename LIST>
struct NthType< -1, LIST >
{
    // ctime assert
};

template <typename LIST>
struct Value : Value< typename LIST::Tail >
{

    typedef Value< LIST > ThisClass;
    typedef Value< typename LIST::Tail >  BaseClass;

    typedef typename LIST::Head HeadType;

    HeadType m_Value;

    //////////////////////////////////////////////////////////////////////////
    /// GetByIndex
    template <int N, bool DMY = false >
    struct SelectByIdx
    {
        static
        typename NthType< N, LIST >::Type & Get( BaseClass & l )
        {
            return l.GetByIdx< N - 1 >();
        }
    };

    template< bool DMY >
    struct SelectByIdx<0, DMY>
    {
        static
        HeadType & Get( ThisClass & l )
        {
            return l.m_Value;
        }
    };

    template <int N>
    typename NthType< N, LIST >::Type & GetByIdx()
    {
        return SelectByIdx< N >::Get( *this );
    }

    //////////////////////////////////////////////////////////////////////////
    /// GetByType
    template <typename K, bool DMY = false>
    struct SelectByType
    {
        static
        K & Get( BaseClass & l )
        {
            return l.GetByType< K >();
        }
    };

    template <bool DMY>
    struct SelectByType< HeadType, DMY >
    {
        static
        HeadType & Get( ThisClass & l )
        {
            return l.m_Value;
        }
    };

    template <typename K >
    K & GetByType()
    {
        return SelectByType< K >::Get( *this );
    }


};

template <>
struct Value< TypeList<> >
{
};

int main(int argc, char* argv[])
{
    typedef TypeList< char, float, int > MyList;

    Value< MyList > myValue;

    std::cout << "Sizeof = " << sizeof( myValue ) << "\n";

    NthType< 0, MyList >::Type c = 'a';
    NthType< 1, MyList >::Type f = 3.2f;

    // warn
    //NthType< 2, MyList >::Type fw = 3.2;

    char & cRef = myValue.GetByIdx< 0 >();
    float & fRef = myValue.GetByIdx< 1 >();

    cRef = 'c';
    fRef = 3.14f;

    char & secondCRef = myValue.GetByType< char >();
    assert( &cRef == &secondCRef );

    float & secondFRef = myValue.GetByType< float >();
    assert( &fRef == &secondFRef );

    return 0;
}

