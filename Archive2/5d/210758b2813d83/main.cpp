/////////////  header file vehicle.h //////////////////
#include <iostream>
#include <string>
#include <memory>

struct vehicle
{
    public:

        using pointer = std::shared_ptr<vehicle> ;

        static pointer create_vehicle( const std::string& id ) ;

        // polymorphic operations on vehicle
        virtual ~vehicle() {}
        virtual void foo() const = 0 ;
        // virtual ..... = 0 ;

    protected:
        vehicle() {} // constructor for normal objects

        struct for_exemplars {};
        vehicle( for_exemplars ) ; // constructor for prototype objects

    private:
        virtual pointer create( const std::string& id ) const = 0 ;
};

/////////////  implementation file vehicle.cc //////////////////
// #includes
namespace
{
    constexpr std::size_t MAX_DERIVED_CLASSES = 1024 ;
    vehicle* exemplars[MAX_DERIVED_CLASSES] ; // chain of responsibility
    std::size_t n_exemplars ;
}

vehicle::vehicle( for_exemplars ) // constructor for prototype objects
{ if( n_exemplars < MAX_DERIVED_CLASSES ) exemplars[ n_exemplars++ ] = this ; }

vehicle::pointer vehicle::create_vehicle( const std::string& id )
{
    vehicle::pointer p { nullptr } ;
    for( std::size_t i = 0 ; i < n_exemplars ; ++i )
        if( ( p = exemplars[i]->create(id) ) ) break ;
    return pointer(p) ;
}


/////////////  header file exemplar_helper.h //////////////////
// #includes

template < typename DERIVED, const char* ID > struct exemplar_helper : vehicle
{
    static const DERIVED exemplar ;

    using vehicle::vehicle ; // inherited constructor

    private: virtual pointer create( const std::string& id ) const override
    {
        if( id == ID ) return pointer{ new DERIVED() } ;
        else return pointer{ nullptr } ;
    }
};

template < typename DERIVED, const char* ID >
const DERIVED exemplar_helper<DERIVED,ID>::exemplar{ for_exemplars() } ;
/*
Note: We are relying on:

There can be more than one definition of a ... static data member
of a class template ... in a program provided that each definition
appears in a different translation unit, and provided the definitions satisfy the
following requirements.  Given such an entity named D defined in more than one
translation unit,

.... requirements elided; they are given in section 3.2 (ODR) of the IS

If the definitions of D satisfy all these requirements, then the program shall
behave as if there were a single definition of D.
*/

// couple of helper macros to make things easy for derived class authors
// who do may not want to understand what is going on behind the scenes

#define BEGIN_DEFINE_VEHICLE( CLASS_NAME ) \
\
extern const char id__##CLASS_NAME[] = #CLASS_NAME ; \
\
struct CLASS_NAME : exemplar_helper< CLASS_NAME, id__##CLASS_NAME > \
{\
    using base = exemplar_helper< CLASS_NAME, id__##CLASS_NAME > ; \
    explicit CLASS_NAME( for_exemplars fe ) : base(fe) {} \

#define END_DEFINE_VEHICLE(CLASS_NAME) \
} ; \
\
template class exemplar_helper< CLASS_NAME, id__##CLASS_NAME > ;
/* Note: this forces instantiation of every member of the class
         we need to ensure that the exemplar object is instantiated */

/////////////  typical component trying to instantiate vehicle objects //////////////////
// #includes

int main()
{
    vehicle::pointer v[] {
                           vehicle::create_vehicle("Car"),
                           vehicle::create_vehicle("Hovercraft"),
                           vehicle::create_vehicle("Ship"),
                           vehicle::create_vehicle("invalid_tag")
                         } ;
    for( auto p : v )
    {
        if(p) p->foo() ;
        else std::cout << "vehicle object could not be instantiated\n" ;
    }
}

// derived classes of vehicle Car, Hovercraft etc. do not need header files
// the classes themselves are not directly accessed by the rest of the program
// they are instantiated via the exemplar / chain of responsibility mechanism
// and accessed via the base class interface


/////////////  implementation file car.cc //////////////////
// #includes

BEGIN_DEFINE_VEHICLE(Car)

    Car() { /* .... */ }

    virtual void foo() const override { std::cout << "Car::foo\n" ; }

    // other overrides

    // implementation

END_DEFINE_VEHICLE(Car)

/////////////  implementation file hovercraft.cc //////////////////
// #includes

BEGIN_DEFINE_VEHICLE(Hovercraft)

    Hovercraft() { /* .... */ }

    virtual void foo() const override { std::cout << "Hovercraft::foo\n" ; }

    // other overrides

    // implementation

END_DEFINE_VEHICLE(Hovercraft)

/////////////  implementation file ship.cc //////////////////
// #includes

BEGIN_DEFINE_VEHICLE(Ship)

    Ship() { /* .... */ }

    virtual void foo() const override { std::cout << "Ship::foo\n" ; }

    // other overrides

    // implementation

END_DEFINE_VEHICLE(Ship)
