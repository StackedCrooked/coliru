#include <iostream>
#include <string>
#include <memory>

struct person
{
    using pointer = std::shared_ptr<person> ;

    virtual ~person() = default ;
    virtual std::string name() const = 0 ;
    virtual int age() const = 0 ;
    virtual pointer best_friend() const  = 0 ;
    virtual void befriend( person::pointer p ) = 0 ;
    virtual std::string faith() const = 0 ;

    virtual std::ostream& print( std::ostream& stm = std::cout ) const
    {
        stm << name() << ' ' << age() << " years (" << faith() << ')' ;
        const auto f = best_friend() ;
        if(f) stm << "  best friend: '" << f->name() << "' (" << f->faith() << ')' ;
        return stm << '\n' ;
    }
};

struct person_impl : person
{
    using pointer = std::shared_ptr<person_impl> ;

    virtual std::string name() const override { return name_ ; }
    virtual int age() const override { return age_ ; }
    virtual person::pointer best_friend() const override { return best_friend_ ; }
    virtual void befriend( person::pointer p ) override { best_friend_ = p ; }

    person_impl( std::string name, int age, person::pointer best_friend = {} )
        : name_(name), age_(age), best_friend_(best_friend) {}

    private:
        const std::string name_ ;
        int age_ ;
        person::pointer best_friend_ ;

        template < typename T > pointer convert( std::string new_name )
        { return std::make_shared<T>( new_name.empty() ? name_ : new_name, age_, best_friend_ ) ; }
        friend struct person_proxy ;
};

struct person_proxy : person
{
    using pointer = std::shared_ptr<person_proxy> ;

    virtual std::string name() const override { return actual->name() ; }
    virtual int age() const override { return actual->age() ; }
    virtual person::pointer best_friend() const override { return actual->best_friend() ; }
    virtual void befriend( person::pointer p ) override { actual->befriend(p) ; }
    virtual std::string faith() const override { return actual->faith() ; }

    explicit person_proxy( person_impl::pointer p ) : actual(p) {}
    void rebind( person_impl::pointer p ) { actual = p ; }

    template< typename T, typename... ARGS > static pointer make( ARGS&&... args )
    { return std::make_shared<person_proxy>( std::make_shared<T>( std::forward<ARGS>(args)... ) ) ; }

    template < typename T > void convert( std::string new_name = "" )
    { rebind( actual->convert<T>(new_name) ) ; }

    private:
        person_impl::pointer actual ;
};

#define DEFINE_PERSON(denomination) \
struct denomination : person_impl \
{ \
    using person_impl::person_impl ; \
    virtual std::string faith() const override { return #denomination ; } \
};

DEFINE_PERSON(wasp)
DEFINE_PERSON(muslim)
DEFINE_PERSON(agnostic)
DEFINE_PERSON(hindu)

int main()
{
    auto mary = person_proxy::make<wasp>( "Mary", 28 ) ;
    auto sandy = person_proxy::make<wasp>( "Sandy", 23, mary ) ;
    mary->befriend(sandy) ;
    mary->print() ;
    sandy->print() ;
    std::cout << "------------------\n" ;

    sandy->convert<muslim>("Fatima") ;
    mary->print() ;
    sandy->print() ;
    std::cout << "------------------\n" ;

    mary->convert<agnostic>("Orchid") ;
    sandy->convert<hindu>("Deepika") ;
    mary->print() ;
    sandy->print() ;
}
