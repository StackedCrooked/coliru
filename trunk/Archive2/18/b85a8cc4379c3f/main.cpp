#include <iostream>

struct person
{
    virtual ~person() = default ;
    virtual std::string name() const = 0 ;
    virtual person* best_friend() const  = 0 ;
    virtual void best_friend( person* p ) = 0 ;
    virtual std::string faith() const = 0 ;

    virtual std::ostream& print( std::ostream& stm ) const
    {
        stm << "person '" << name() << "' (" << faith() << ',' << this << ")" ;
        const auto f = best_friend() ;
        if(f) stm << " with best friend: '" << f->name() << "' (" << f->faith() << ',' << f << ')' ;
        return stm << '\n' ;
    }
};

struct person_identity_proxy : person
{
    virtual std::string name() const override { return actual->name() ; }
    virtual person* best_friend() const override { return actual->best_friend() ; }
    virtual void best_friend( person* p ) override { actual->best_friend(p) ; }
    virtual std::string faith() const override { return actual->faith() ; }
    virtual std::ostream& print( std::ostream& stm ) const override { return actual->print(stm) ; }

    explicit person_identity_proxy( person* p ) : actual(p) {}
    void rebind( person* p ) { actual = p ; }

    private: person* actual ;
};

struct person_impl : person
{
    virtual std::string name() const override { return name_ ; }
    virtual person* best_friend() const override { return best_friend_ ; }
    virtual void best_friend( person* p ) override { best_friend_ = p ; }

    explicit person_impl( std::string name ) : name_(name) {}
    person_impl( std::string name, person* best_friend ) : name_(name), best_friend_(best_friend) {}

    private:
        const std::string name_ ;
        person* best_friend_ = nullptr ;
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
    wasp sandy("Sandy") ;
    person_identity_proxy proxy( &sandy ) ;

    wasp mary( "Mary", &proxy ) ;
    mary.print(std::cout) ;

    muslim fatima("fatima") ;
    proxy.rebind( &fatima ) ;
    mary.print(std::cout) ;

    agnostic shazia( "Shazia" ) ;
    proxy.rebind( &shazia ) ;
    mary.print(std::cout) ;
}
