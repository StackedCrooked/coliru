#include <iostream>
#include <string>
#include <memory>

struct person
{
    virtual ~person() = default ;
    virtual std::string name() const = 0 ;
    virtual int age() const = 0 ;
    virtual person* best_friend() const  = 0 ;
    virtual void best_friend( person* p ) = 0 ;
    virtual std::string faith() const = 0 ;
    virtual std::string pet() const = 0 ;
    virtual void pet( std::string pn )= 0 ;

    virtual std::ostream& print( std::ostream& stm = std::cout ) const
    {
        stm << "person '" << name() << "' " << age() << " years (" << faith() << ',' << this << ")" ;
        const auto f = best_friend() ;
        if(f) stm << "\n\twith best friend: '" << f->name() << "' (" << f->faith() << ',' << f << ')' ;
        const std::string& p = pet() ;
        if( !p.empty() ) std::cout << "\n\tand pet: '" << p << '\'' ;
        return stm << '\n' ;
    }
};

struct person_impl : person
{
    virtual std::string name() const override { return name_ ; }
    virtual int age() const override { return age_ ; }
    virtual person* best_friend() const override { return best_friend_ ; }
    virtual void best_friend( person* p ) override { best_friend_ = p ; }
    virtual std::string pet() const override { return pet_ ; }
    virtual void pet( std::string pn ) override { pet_ = pn ; }

    person_impl( std::string name, int age ) : name_(name), age_(age) {}
    person_impl( std::string name, int age, person* best_friend )
        : name_(name), age_(age), best_friend_(best_friend) {}
    person_impl( std::string name, int age, std::string pet )
        : name_(name), age_(age), pet_(pet) {}
    person_impl( std::string name, int age, person* best_friend, std::string pet )
        : name_(name), age_(age), best_friend_(best_friend), pet_(pet) {}

    private:
        const std::string name_ ;
        int age_ ;
        person* best_friend_ = nullptr ;
        std::string pet_ ;

        template < typename T > person_impl* convert( std::string new_name )
        {
            person_impl* p = new T( new_name, age_, best_friend_, pet_ ) ;
            delete this ;
            return p ;
        }
        friend struct person_identity_proxy ;
};

struct person_identity_proxy : person
{
    ~person_identity_proxy() { delete actual ; }
    virtual std::string name() const override { return actual->name() ; }
    virtual int age() const override { return actual->age() ; }
    virtual person* best_friend() const override { return actual->best_friend() ; }
    virtual void best_friend( person* p ) override { actual->best_friend(p) ; }
    virtual std::string faith() const override { return actual->faith() ; }
    virtual std::string pet() const override { return actual->pet() ; }
    virtual void pet( std::string pn ) override { actual->pet(pn) ; }

    explicit person_identity_proxy( person_impl* p ) : actual(p) {}

    void rebind( person_impl* p ) { actual = p ; }
    person_impl* get() { return actual ; }

    template< typename T, typename... ARGS >
    static person_identity_proxy* make( ARGS&&... args )
    { return new person_identity_proxy( new T( std::forward<ARGS>(args)... ) ) ; }

    template < typename T > void convert( std::string new_name )
    { rebind( actual->convert<T>(new_name) ) ; }

    private: person_impl* actual ;
};

struct wasp : person_impl
{
    using person_impl::person_impl ;
    virtual std::string faith() const override { return "wasp" ; }
};

struct muslim : person_impl
{
    using person_impl::person_impl ;
    virtual std::string faith() const override { return "muslim" ; }
};

struct agnostic : person_impl
{
    using person_impl::person_impl ;
    virtual std::string faith() const override { return "agnostic" ; }
};

int main()
{
    auto person_a = person_identity_proxy::make<wasp>( "Mary", 28, "Felix" ) ;
    auto person_b = person_identity_proxy::make<wasp>( "Sandy", 30, person_a, "Brandy" ) ;
    person_a->best_friend(person_b) ;

    person_a->print() ;
    person_b->print() ;

    person_b->convert<muslim>("Fatima") ;
    person_a->print() ;
    person_b->print() ;

    person_a->convert<agnostic>("Orchid") ;
    person_a->print() ;
    person_b->print() ;
}
