
#include <iostream>

//! Empty class or dummy class for specializations.
struct Empty {};

//! Generic TypeList.
//! Use like "TypeList< int, float >".
//! Currently supports limited number of arguments (no variadic templates available).
template<
    class T01 = Empty, class T02 = Empty, class T03 = Empty, class T04 = Empty, class T05 = Empty,
    class T06 = Empty, class T07 = Empty, class T08 = Empty, class T09 = Empty, class T10 = Empty,
    class T11 = Empty, class T12 = Empty, class T13 = Empty, class T14 = Empty, class T15 = Empty
>
struct TypeList;

typedef TypeList<> EmptyTypeList;



namespace Impl{

    //! Recursive definition of types.
    template< class DEF, int NUM, class TAIL >
    struct RecTypes
    {
        typedef DEF     Type;
        typedef TAIL    Tail;
        enum{ Id = CNTR };
    };

    template<>
    struct RecTypes<Empty,Empty>
    {
        typedef DEF     Type;
        enum{ Id = 0 };
    };

    template< class LIST, class PREVSEL = Empty, int CNTR = 0 >
    struct Selector
    {
        typedef typename LIST::Head Head;
        typedef typename LIST::Tail Tail;
        typedef RecTypes< Head, CNTR, RecTypes<Tail > RecType;

        typedef typename Selector< typename LIST::Tail, CNTR + 1 >::Type PrevType;
    };

    template< int CNTR >
    struct Selector< EmptyTypeList, CNTR >
    {
        typedef RecTypes< Empty, CNTR, Empty > RecType;
        typedef Empty Type;
        enum{ Id = CNTR };
    };

}


//! Forwards:
template< class, class > struct RecValue;
template< class, class > struct RecType;



//! Generic TypeList.
//! Use like "TypeList< int, float >".
//! Currently supports limited number of arguments (no variadic templates available).
template<
    class T01, class T02, class T03, class T04, class T05,
    class T06, class T07, class T08, class T09, class T10,
    class T11, class T12, class T13, class T14, class T15
>
struct TypeList
{
    typedef T01 Head;
    typedef TypeList< T02, T03, T04, T05, T06, T07, T08, T09, T10, T11, T12, T13, T14, T15 > Tail;

    typedef Impl::Builder< Head, Tail >                 Builder;

    typedef RecType< Head, typename Tail::Types >       Types;
    typedef RecValue< Head, typename Tail::Values >     Values;
    enum{ Length = Tail::Length + 1 };
};

//! Specialization for the empty list.
template<>
struct TypeList<Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty>
{
    typedef Impl::RecTypes< Empty, EmptyTypeList >      RecTypes;

    typedef Empty     Types;
    typedef Empty     Values;
    enum{ Length = 0 };
};




template< class DEF, class TAIL >
struct RecBuilder
{
    typedef DEF     Type;
    typedef TAIL    Tail;
};




//! Recursive definition of values.
template< class DEF, class TAIL >
struct RecValue
{
    TAIL    m_Tail;
    DEF     m_Value;
};

//! Empty tail.
template< class DEF >
struct RecValue< DEF, Empty >
{
    DEF     m_Val;
};



namespace Impl {
    template< class LIST, class FTOR >
    struct AllTypesImpl
    {
        static void Run( FTOR& ftor )
        {
            EntryInfo< typename LIST::Head, 0, typename LIST::Tail > entry;
            ftor.ApplyType( entry );
            AllTypesImpl< typename LIST::Tail, FTOR >::Run( ftor );
        }
    };

    template< class FTOR >
    struct AllTypesImpl< EmptyTypeList, FTOR >
    {
        static void Run( FTOR& ftor )
        {}
    };


}
template< class ENTRY, int ID, class NEXT >
struct EntryInfo
{
    typedef ENTRY   EntryType;
    typedef NEXT    NextType;
    enum{ Id = ID };
};




template< class LIST, class FTOR >
void ForAllTypes( FTOR& ftor )
{
    Impl::AllTypesImpl< LIST, FTOR >::Run( ftor );
}

int main(int argc, char* argv[])
{
    // gives "A=1 B=0 C=0"
    std::cout << "A=" << Check<A>::value << " B=" << Check<B>::value << " C=" << Check<C>::value << std::endl;
    // want same output with FuncT, but doesn't compile:
    // error: ‘&A::FuncT’ is not a valid template argument for type ‘void (B::*)(int)’ because it is of type ‘void (A::*)(int)’
    std::cout << "B=" << Check<B>::valueT << std::endl;
    return 0;
}
